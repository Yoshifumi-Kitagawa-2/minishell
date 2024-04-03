NAME = minishell
SRCDIR = ./srcs/
SRCS = 0_main.c 1_make_environ.c 2_1_tokenize.c  2_2_tokenize_utils.c 2_3_tokenize_handles.c 2_4_tokenize_handle_word.c 2_5_tokenize_check.c 2_6_tokenize_check_2.c\
		 3_1_expand.c 3_2_expand.c 3_3_expand.c 3_4_expand.c 3_5_expand.c 3_6_expand.c 3_7_token_list_to_array.c 3_8_search_env.c \
		 4_1_pipe.c 4_2_pipe.c 4_3_pipe.c 4_4_pipe.c 4_5_pipe.c 4_6_pipe.c 4_7_pipe.c 4_8_pipe.c 4_9_pipe.c\
		 5_1_signal.c 5_2_signal.c 6_1_exit_builtin.c 6_2_env_builtin.c 6_3_echo_builtin.c 6_4_1_cd_builtin.c 6_4_2_cd_builtin.c 6_5_pwd_builtin.c \
		 6_6_1_export_builtin.c 6_6_2_export_builtin.c 6_6_3_export_builtin.c 6_6_4_export_builtin.c 6_7_unset_builtin.c \
		 7_destructer.c 8_1_error.c 8_2_error.c 8_3_dprintf.c utils1.c utils2.c


CC = cc
CFLAGS = -I $(shell brew --prefix readline)/include -Wall -Wextra -Werror
LDFLAGS = -lreadline -lhistory -L$(shell brew --prefix readline)/lib
RM = rm -rf

OBJDIR = ./obj/
OBJS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

LIBDIR = ./libft
GNLDIR = ./libgnl

all: $(OBJDIR) $(NAME)

$(OBJDIR) :
	mkdir -p obj

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	make -C $(LIBDIR)
	make -C $(GNLDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -L $(LIBDIR) -L $(GNLDIR) -lft -lgnl
	echo > ~/.inputrc set echo-control-characters off

clean	:
	$(RM) $(OBJDIR)
	make -C $(LIBDIR) clean
	make -C $(GNLDIR) clean

fclean	:	
	make -C $(LIBDIR) fclean
	make -C $(GNLDIR) fclean
	$(RM) $(OBJDIR)
	$(RM) $(NAME)

re:	fclean all

test: all
	./test.sh
	
.PHONY:		all clean fclean re