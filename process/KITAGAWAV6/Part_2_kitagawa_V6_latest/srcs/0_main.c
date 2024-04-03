/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:19:10 by yokitaga          #+#    #+#             */
/*   Updated: 2023/04/06 18:31:07 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_argv(char **argv)
{
	int	len;

	len = 0;
	while (*argv)
	{
		len++;
		argv++;
	}
	return (len);
}

void	process_line(char *line, t_environ **list)
{
	t_token	*token;
	char	**array;
	int		argc;

	token = tokenize(line);
	if (g_signal.status == 258 && g_signal.other_code == TRUE)
	{
		free_token(token);
		return ;
	}
	g_signal.pipe_count = count_pipe(token);
	if (token->kind == TOKEN_EOF)
		;
	else
	{
		array = expand(token, *list);
		argc = count_argv(array);
		pipex(argc, array, list);
	}
	unlink("./.heredoc");
	free_token(token);
}

void	init_g_signal(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	g_signal.input_fd = dup(0);
	g_signal.output_fd = dup(1);
	g_signal.do_split = 2;
	g_signal.pipe_count = 0;
	g_signal.not_parse_flag = 0;
	g_signal.not_expand_flag = 0;
	g_signal.expand_in_heredoc = FALSE;
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_environ	*list;

	rl_outstream = stderr;
	list = make_environ(envp);
	g_signal.other_code = FALSE;
	g_signal.unset_pwd_flag = FALSE;
	while (1)
	{
		if (g_signal.other_code == FALSE)
			g_signal.status = 0;
		init_g_signal(argc, argv);
		set_signal();
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (line && !(*line == '\0' || is_space(line)))
			g_signal.other_code = FALSE;
		if (*line != '\0')
			add_history(line);
		process_line(line, &list);
		free(line);
	}
	write(2, "exit\n", 5);
	free_list(list);
	return (g_signal.status);
}
