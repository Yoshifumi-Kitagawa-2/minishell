/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_3_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:12:35 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/04/05 11:23:55 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	writing_for_one(int num, char **array, t_environ *list, char *line)
{
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, array[num]) == 0)
		{
			free(line);
			break ;
		}
		if (g_signal.not_expand_flag == 0 && ft_strchr(line, '$'))
		{
			while (ft_strchr(line, '$'))
				line = double_variable_expand(line, list);
		}
		write(g_signal.heredoc_fd, line, ft_strlen(line));
		write(g_signal.heredoc_fd, "\n", 1);
		free(line);
	}
}

void	writing_for_not_one_v1(char *line, char **array, int num)
{
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, array[num]) == 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
}

void	writing_for_not_one_v2(int num, char **array,
		t_environ *list, char *line)
{
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, array[num]) == 0)
		{
			free(line);
			break ;
		}
		if (g_signal.not_expand_flag == 0 && search_env(line + 1, list))
		{
			tmp = search_env(line + 1, list);
			free(line);
			line = tmp;
		}
		write(g_signal.heredoc_fd, line, ft_strlen(line));
		write(g_signal.heredoc_fd, "\n", 1);
		free(line);
	}
}

void	write_to_heredoc_one(char **array, int i, t_environ *list)
{
	char	*line;

	line = NULL;
	g_signal.heredoc_fd = open(".heredoc",
			(O_WRONLY | O_CREAT | O_TRUNC), 0644);
	if (g_signal.heredoc_fd == -1)
		function_error("open");
	heredoc_signal();
	writing_for_one(i + 1, array, list, line);
	dup2(g_signal.input_fd, 0);
	close(g_signal.heredoc_fd);
}

void	write_to_heredoc_not_one(char **array, int i,
		int *heredoc_flag, t_environ *list)
{
	char	*line;

	line = NULL;
	if (ft_strcmp(array[i + 4], "<<") == 0)
		return ;
	heredoc_signal();
	*heredoc_flag = 1;
	g_signal.heredoc_fd = open(".heredoc",
			(O_WRONLY | O_CREAT | O_TRUNC), 0644);
	if (g_signal.heredoc_fd == -1)
		function_error("open");
	writing_for_not_one_v1(line, array, i + 1);
	if (g_signal.other_code == FALSE)
		writing_for_not_one_v2(i + 3, array, list, line);
	dup2(g_signal.input_fd, 0);
	close(g_signal.heredoc_fd);
}
