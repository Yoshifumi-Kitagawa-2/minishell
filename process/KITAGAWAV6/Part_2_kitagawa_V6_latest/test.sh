#!/bin/bash
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
RESET="\033[0m"
OK=$GREEN"OK"$RESET
NG=$RED"NG"$RESET

cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

cat <<EOF | gcc -xc -o print_args -
#include <stdio.h>
int main(int argc, char *argv[]) {
 for (int i = 0; argv[i]; i++)
  printf("argv[%d] = %s\n", i, argv[i]);
}
EOF

cat <<EOF | gcc -xc -o exit42 -
int main() { return 42; }
EOF

print_desc() {
 echo -e $YELLOW"$1"$RESET
}

cleanup() {
 rm -f cmp out a.out print_args exit42 infinite_loop no_exec_perm no_read_perm
}

assert() {
 COMMAND="$1"
 shift
 printf '%-60s:' "[$COMMAND]"
 # exit status
 echo -n -e "$COMMAND" | bash >cmp 2>&-
 expected=$?
 for arg in "$@"
 do
  mv "$arg" "$arg"".cmp"
 done
 echo -n -e "$COMMAND" | ./minishell >out 2>&-
 actual=$?
 for arg in "$@"
 do
  mv "$arg" "$arg"".out"
 done

 diff cmp out >/dev/null && echo -e -n "  diff $OK" || echo -e -n "  diff $NG"

 if [ "$actual" = "$expected" ]; then
  echo -e -n "  status $OK"
 else
  echo -e -n "  status $NG, expected $expected but got $actual"
 fi
 for arg in "$@"
 do
  echo -n "  [$arg] "
  diff "$arg"".cmp" "$arg"".out" >/dev/null && echo -e -n "$OK" || echo -e -n "$NG"
  rm -f "$arg"".cmp" "$arg"".out"
 done
 echo
}

echo "############################## minishell test result ################################"

echo "################ Empty line (EOF) #################"
assert ''
assert '          '
assert '					'

echo "################ Absolute path commands without args #################"
assert '/bin/pwd'
assert '/bin/echo'
assert '/bin/ls'

echo "################ Search command path without args #################"
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'

echo "################ other command #################"
assert 'A='
assert 'A=a'
assert 'A=a B=b'

echo "################ command not found #################"
assert 'a.out'
assert 'nosuchfile'
assert '""'
assert '..'
assert '""'
assert "''"
assert 'A'

echo "################ is a directory #################"
assert './'
assert '/'
assert '/etc'
assert '/etc/'
assert '////'

echo "################ Permission denied #################"
echo "int main() { }" | gcc -xc -o no_exec_perm -
chmod -x no_exec_perm
assert 'no_exec_perm'
assert './no_exec_perm'
echo "int main() { }" | gcc -xc -o no_read_perm -
chmod -r no_read_perm
assert 'no_read_perm'
assert './no_read_perm'

mkdir -p /tmp/a /tmp/b
echo "int main() { return 1; }" | gcc -xc -o /tmp/a/simple_test -
echo "int main() { return 2; }" | gcc -xc -o /tmp/b/simple_test -

print_desc "/tmp/a /tmp/b both with permission"
assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'

print_desc "/tmp/a /tmp/b both without permission"
chmod -x /tmp/a/simple_test; chmod -x /tmp/b/simple_test;
assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'

print_desc "a with permission, b without permission"
chmod +x /tmp/a/simple_test; chmod -x /tmp/b/simple_test;
assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'

print_desc "a without permission, b with permission"
chmod -x /tmp/a/simple_test; chmod +x /tmp/b/simple_test;
assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'

echo "################# echo #################"
assert 'echo'
assert 'echo hello'
assert 'echo hello "    " world'
assert 'echo -n'
assert 'echo -n hello'
assert 'echo -n hello world'
assert 'echo hello -n'
assert 'echo hello -n world'
assert "echo 'aaaa'"
assert 'A=a echo a'
assert 'echo a b "" c d'
assert 'echo -nnnnnnnnnnn aaaa'
assert 'echo -n -n -n aaaa bbbb'
assert 'echo -n -n -n aaaa bbbb -n -n -n'


echo "################# exit #################"
assert 'exit'
assert 'exit 42'
assert 'exit ""'
assert 'exit hello'
assert 'exit 42Tokyo'
assert 'exit 1 2'
assert 'exit a 2 3'
assert 'exit 1 a a'
assert 'exit 1 | exit 2 | eixt 3\necho$?'
assert 'exit -1'
assert 'exit -42'
assert 'exit 1000000000000000000000' 

echo "################ Special Parameter $? #################"
assert 'echo $?'
assert 'invalid\necho $?\necho $?'
assert 'exit42\necho $?\necho $?'
assert 'exit42\n\necho $?\necho $?'

echo "################# unquoted word#################"
assert 'ls "'
assert 'echo "hello    world     '
assert 'echo "aaaa'
assert "echo 'aaaa"
assert "'"
assert '"'

echo "################# single quote#################"
assert "./print_args 'hello   world' '42Tokyo'"
assert "echo 'hello   world' '42Tokyo'"
assert "echo '\"hello   world\"' '42Tokyo'"
assert "echo $'aaaa'"
assert "echo '<'"
assert "echo '>'"
assert "echo '<|'"

echo "################# double quote#################"
assert './print_args "hello   world" "42Tokyo"'
assert 'echo "hello   world" "42Tokyo"'
assert "echo \"'hello   world'\" \"42Tokyo\""
assert 'echo $"aaaa"'
assert 'echo $hoge"$USER"'
assert 'echo $hoge"$USERa"'

echo "################# combination#################"
assert "echo hello'      world'"
assert "echo hello'  world  '\"  42Tokyo  \""
assert 'export TEST=aaaa\necho $"$TEST"'
assert "export TEST=aaaa\necho $'\$TEST'"

echo "################# env #################"
print_desc "Output of 'env' differs, but it's ok."
assert 'env'
assert 'env | grep hoge | sort'

echo "################# export #################"
assert 'export'
print_desc "Output of 'export' differs, but it's ok."
assert 'export  tests\n export | grep tests\nenv | grep tests'
assert 'export  tests=\n export | grep tests\nenv | grep tests'
assert 'export  tests=a\n export | grep tests\nenv | grep tests'
assert 'export | grep nosuch | sort'
assert 'export nosuch\n export | grep nosuch | sort'
assert 'export nosuch=fuga\n export | grep nosuch | sort'
assert 'export nosuch=fuga hoge=nosuch\n export | grep nosuch | sort'
assert 'export [invalid]'
assert 'export [invalid_nosuch]\n export | grep nosuch | sort'
assert 'export [invalid]=nosuch\n export | grep nosuch | sort'
assert 'export [invalid] nosuch hoge=nosuch\n export | grep nosuch | sort'
assert 'export nosuch [invalid] hoge=nosuch\n export | grep nosuch | sort'
assert 'export nosuch hoge=nosuch [invalid]\n export | grep nosuch | sort'
assert 'export nosuch="nosuch2=hoge"\nexport $nosuch\n export | grep nosuch | sort'
echo ↓hoge not exist↓
assert 'export hoge+=hoge\n export | grep hoge'
export hoge=hoge
echo ↓hoge exist↓
assert 'export hoge+=hoge\n export | grep hoge'
unset hoge

echo "################# unset #################"
export hoge fuga=fuga
assert 'unset'
assert 'unset ""'
assert 'unset '\'''\'''
assert 'unset hoge'
assert 'unset fuga'
assert 'unset nosuch'
assert 'unset [invalid]'
assert 'unset hoge fuga'
assert 'unset hoge nosuch fuga'
assert 'unset fuga \n export | echo $fuga'
assert 'unset [invalid] fuga \n echo $fuga'
assert 'unset PATH \n ls'
assert 'unset PATH \n /bin/ls'

echo "################# cd #################"
assert 'cd'
assert 'cd .'
assert 'cd ..'
assert 'cd ///'
assert 'cd /tmp'
assert 'cd /tmp/'
assert 'cd /tmp///'
assert 'cd /../../../././.././'
assert 'cd src'
assert 'cd nosuch'
assert 'unset HOME\ncd'

assert 'cd \n echo $PWD'
assert 'cd \n echo $PWD'
assert 'cd .\n echo $PWD'
assert 'cd ..\n echo $PWD'
assert 'cd ///\n echo $PWD'
assert 'cd /tmp\n echo $PWD'
assert 'cd /tmp/\n echo $PWD'
assert 'cd /tmp///\n echo $PWD'
assert 'cd /../../../././.././\n echo $PWD'
assert 'cd src\n echo $PWD'
assert 'cd\ncd -'
assert 'cd --'
assert 'unset HOME\ncd \n echo $PWD'

echo "################# pwd #################"
assert 'pwd'
assert 'cd\npwd'
assert 'cd src\npwd'
assert 'cd /etc\npwd'
assert 'cd . \n pwd \n echo $PWD $OLDPWD'
assert 'cd .. \n pwd \n echo $PWD $OLDPWD'
assert 'cd /// \n pwd \n echo $PWD $OLDPWD'
assert 'cd /tmp/// \n pwd \n echo $PWD $OLDPWD'
assert 'unset PWD\necho $PWD'
assert 'unset PWD\npwd'
assert 'unset PWD\npwd\ncd /etc\npwd'
assert 'unset PWD \n cd \n echo $PWD \ncd /tmp\necho $PWD'
assert 'unset PWD\ncd\necho $OLDPWD\ncd /tmp\necho $OLDPWD'
assert 'unset PWD\ncd\nexport|grep PWD\ncd /tmp\nexport|grep PWD'
assert 'unset PWD\ncd\nenv|grep PWD\ncd /tmp\nenv|grep PWD'

echo "################# Redirecting output#################"
assert 'echo hello >hello.txt' 'hello.txt'
assett 'echo -n aaa > outfile' 'outfile'
assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'
assert 'echo a > test1  b' 'test1'
assert 'echo c > test2 "d   ef"' 'test2'
assert 'cat test1 > test3 test2' 'test3'
assert 'cat test1'
assert 'cat test2'
assert 'cat < test3 test2'
assert 'cat test1 > test3 > test2' 'test3'
assert 'cat test1'
assert 'cat test2'
assert 'echo > >'
assert 'echo aa > > test1'
assert 'echo aa > 1 > 2 > 3 b c d e f' '1' '2' '3'
assert 'echo aa > 1 > 2 > 3 b c d e f > 4' '1' '2' '3' '4'
rm -f hello.txt f1 f2 f3 test1 test2 test3 outfile

echo "################# Redirecting input#################"

assert 'cat < Makefile'
echo hello >f1
echo world >f2
echo 42Tokyo >f3
assert 'cat <f1<f2<f3'
rm -f f1 f2 f3
assert 'cat <hoge'

echo "############### Appending Redirected output #################"
assert 'pwd >>pwd.txt' 'pwd.txt'
assert 'pwd >>pwd.txt \n pwd >>pwd.txt' 'pwd.txt'
assert 'echo hello >>hello1.txt>>hello2.txt>>hello3.txt' 'hello1.txt' 'hello2.txt' 'hello3.txt'
assert 'echo hello >>hello1.txt>>hello2.txt>>hello3.txt aa bb cc' 'hello1.txt' 'hello2.txt' 'hello3.txt'
assert 'echo hello >>hello1.txt>>hello2.txt>>hello3.txt aa bb cc >> hello4.txt' 'hello1.txt' 'hello2.txt' 'hello3.txt' 'hello4.txt'

assert 'echo aa >> >> test1'
rm -f hello1.txt hello2.txt hello3.txt pwd.txt test1

echo "################# Here Document #################"
assert '<< "EOF"\nEOF'
assert 'cat <<  ""\n""'
assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
assert 'cat <<EOF\nhello\nworld'
assert 'cat <<E"O"F\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF   \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
assert 'cat <<"EOF" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
assert 'cat <<EO"F" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
export EOF="eof"
assert 'cat <<$EOF         \neof\n$EOF\nEOF'
assert 'cat <<"$EOF"       \neof\n$EOF\nEOF'
assert '<< 1 << 2 << 3 cat  \n1\n2\n3\n'

echo "################# Redirect combination #################"
assert 'cat < Makefile > out.txt'
assert 'cat < Makefile > out.txt > out2.txt'
assert 'cat < Makefile > out.txt > out2.txt > out3.txt'
rm -f out.txt out2.txt out3.txt
assert '> test \n< test\n>>test\n<<test\ntest\n'
rm -f test

echo "################ Pipe #################"
assert 'ls | cat'
assert 'ls | cat | cat'
assert 'cat | ls\n'
assert 'cat | cat | ls\n\n'
assert 'echo a | echo b | echo c'
assert 'env | grep PATH'
assert 'cat Makefile | grep minishell'
assert '|'
assert '| echo aaaa'

echo "################ Environment Variable #################"
assert 'echo $'
assert 'echo $USER'
assert 'echo $1USER'
assert 'echo $12USER'
assert 'echo $USER$PATH$TERM'
assert 'echo "$USER  $PATH   $TERM"'
assert 'echo aaa > $NO_EXIST'
assert 'export TEST="-n hello"\necho $TEST'
assert 'export TEST="a=b=c=d"\necho $TEST'
export TEST="test"
assert 'export $TEST $NO_EXIST $NO_EXIST2'
assert 'export $NO_EXIST $TEST $NO_EXIST2'
assert 'export $NO_EXIST $NO_EXIST2 $TEST'
unset TEST
assert 'export a=" "\necho$a-a'


cleanup