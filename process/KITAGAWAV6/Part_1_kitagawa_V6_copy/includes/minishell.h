/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:43:55 by yokitaga          #+#    #+#             */
/*   Updated: 2023/04/01 16:19:46 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libgnl/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <string.h>
# include <stdbool.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdarg.h>
# include <errno.h>

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'

# define RIGHT 1
# define MID 0
# define LEFT -1

# define STDIN 0
# define STDOUT 1

# define TRUE 1
# define FALSE 0

typedef enum e_error_kind{
	TOKENIZE_ERROR,
}t_error_kind;

typedef enum e_token_kind{
	TOKEN_WORD,
	TOKEN_METACHAR,
	TOKEN_CONTROL_OP,
	TOKEN_EOF,
}t_token_kind;

typedef struct s_token	t_token;

struct	s_token{
	char			*word;
	t_token_kind	kind;
	t_token			*next;
};

typedef struct s_environ {
	char				*key;
	char				*value;
	struct s_environ	*next;
}t_environ;

typedef struct s_info{
	int			input_fd;
	int			output_fd;
	int			**pipefd;
	int			argc;
	char		**cmd;
	char		**argv;
	int			argv_count;
	char		**path;
	t_environ	*list;
	int			heredoc_flag;
	int			*pipe_place;
}t_info;

typedef struct s_signal {
	int		status;
	int		heredoc_fd;
	int		input_fd;
	int		output_fd;
	int		other_code;
	int		do_split;
	int		pipe_count;
	int		not_expand_flag;
	bool	expand_in_heredoc;
	bool	unset_pwd_flag;
}t_signal;

t_signal				g_signal;

char		**token_list_to_array(t_token *token);
void		free_token(t_token *token);
void		free_array(char **array);
void		free_list(t_environ *list);
void		function_error(char *function_name);
void		tokenize_error(char *message, char **rest, char *line);
void		tokenize_error_2(char *message, char *word);
void		assert_error(const char *msg);
void		export_not_valid_identifier(char *argv);
void		unset_not_valid_identifier(char *argv);
void		err_exit(const char *location, const char *msg);
void		command_not_found(const char *location);
void		file_not_found(const char *filename);
void		ambiguous_redirect(char *filename);
int			my_dprintf(int fd, const char *fmt, ...);
void		pipex(int argc, char *argv[], t_environ **list);
int			count_heredoc(char **argv);
char		**list_to_array(t_environ *list);
int			count_pipe(t_token *token);
t_token		*tokenize(char *line);
bool		is_blank(char c);
bool		is_metacharacter(char c);
bool		is_control_operator(char *s);
t_token		*new_token(t_token_kind kind);
void		append_token(t_token **head, t_token *new);
t_token		*handle_metacharacter(char **rest, char *line);
t_token		*handle_contorol_op(char **rest, char *line);
char		*ft_strndup(char *str, size_t n);
bool		check_single_quote(char **line);
bool		check_double_quote(char **line);
void		get_end(char **line);
t_token		*handle_word(char **rest, char *line);
bool		check_redirect_token(t_token *token);
void		check_and_sort_tokens(t_token **head);
void		check_pipe_place(t_token **head);
char		**expand(t_token *tok, t_environ *list);
t_environ	*make_environ(char **envp);
t_environ	*new_list(char *envp);
void		list_add_back(t_environ **list, t_environ *new);
int			set_signal(void);
int			set_signal_child(void);
int			set_signal_parent(void);
int			heredoc_signal(void);
char		*search_env(char *key, t_environ *list);
int			ft_strcmp(char *str1, char *str2);
void		cd_builtin(t_info *info);
void		set_old_and_new_pwd(t_environ *list, char *new_pwd_dup);
void		echo_builtin(t_info *info, int j);
void		env_builtin(t_info *info);
void		exit_builtin(t_info *info);
void		pwd_builtin(t_info *info);
void		export_builtin(t_info *info, t_environ **list);
int			ft_strchr_index(const char *str, char c);
void		update_env(char *arg, t_environ **list);
void		add_new_env(char *arg, t_environ **list);
bool		check_argv_no_such_env(t_info *info);
bool		check_add_or_not(char *arg);
void		add_env_value(char *arg, t_environ **list);
void		list_add_back_export(t_environ **list, char *key, char *value);
t_environ	*new_node(char *key, char *value);
int			not_allowed_variant_character(char *key);
void		unset_builtin(t_info *info, t_environ **list);
char		**x_double_str_malloc(int num);
char		*x_str_malloc(int num);
char		*x_strdup(char *str);
int			**x_double_int_malloc(int num);
int			*x_int_malloc(int num);
char		*create_new_word_if_null(char *var, t_environ *list);
void		create_new_word_if_not_null(char **new_word, \
					char *var, t_environ *list);
void		write_to_heredoc_one(char **array, int i, t_environ *list);
void		write_to_heredoc_not_one(char **array, int i, \
					int *heredoc_flag, t_environ *list);
void		just_append(t_token *tok, char **p, char **new_word);
void		expand_variable(char **p, char **new_word, t_environ *list);
bool		handle_after_doll(char **p, char **new_word, t_environ *list);
void		expansion(char **p, char **new_word, t_environ *list);
void		quote_removal(t_token *tok, t_environ *list);
void		remove_double_quote(char **p, char **new_word, t_environ *list);
void		remove_single_quote(char **p, char **new_word);
char		*double_variable_expand(char *new_word, t_environ *list);
void		append_char(char **s, char c);
int			is_variable_character(char c);
char		**make_path_list(t_environ *list);
int			*place_pipe(t_info *info);
void		safty_free(char **str);
int			check_builtin(char *argv);
void		make_info_argv(t_info *info, int end, int start);
int			check_redirect(t_info *info);
void		do_builtin(char *argv, t_environ **list, t_info *info);
void		multiple_pipes(t_info *info, t_environ **list);
void		remove_redirect(char **tmp, t_info *info, int i);
int			branch_do_v2(t_info *info, int i, int heredoc_count);
int			branch_do_v1(t_info *info, int i, int heredoc_count);
void		do_input(t_info *info, int i);
void		do_output(t_info *info, int i);
void		do_heredoc_one(t_info *info, int i);
void		do_heredoc_not_one(t_info *info, int i);
void		do_append(t_info *info, int i);
int			detect_something(t_info *info, int i);
int			count_splitable(t_info *info, int start, int end);
char		*make_exepath(char *path, char *command);
void		do_fd(t_info *info, int i);
void		execute_check_equal(t_info *info, int j);
void		check_equal(t_info *info, int *j);
void		do_mix_builtin(t_info *info, t_environ **list, int i);
char		*create_path(t_info *info, int j);
bool		path_null(char *path);
void		malloc_error_free(int **pipefd, int i);
void		check_variable_character(char **var, char **p);
int			yatto_owari(char **key, int *i);
int			is_space(char *str);
void		handle_empty_str(char **p, char **new_word);
void		move_space(t_info *info, int start, int *i, int *count);
void		cut_wstatus(int wstatus);
char		*x_strndup(char *str, int i);
void		check_private(char *new_pwd, t_info *info);

#endif	