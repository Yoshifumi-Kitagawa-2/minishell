/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_1_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 23:07:46 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/04/02 18:27:07 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	info_init(t_info *info, int argc, char **argv, t_environ *list)
{
	info->input_fd = 0;
	info->output_fd = 1;
	info->argc = argc;
	info->argv = NULL;
	info->cmd = argv;
	info->path = make_path_list(list);
	info->list = list;
	info->pipefd = NULL;
	info->pipe_place = place_pipe(info);
	info->heredoc_flag = 0;
}

void	ft_environ_list_clear(t_environ **list)
{
	t_environ	*tmp;

	if (list)
	{
		while (*list)
		{
			tmp = (*list)->next;
			free(*list);
			*list = tmp;
		}
		list = NULL;
	}
}

void	finish(t_info *info)
{
	int	i;

	i = 0;
	if (info->path)
		safty_free(info->path);
	if (info->cmd)
		safty_free(info->cmd);
	free(info->pipe_place);
	if (info->pipefd)
	{
		while (i < g_signal.pipe_count)
		{
			free(info->pipefd[i]);
			i++;
		}
		free(info->pipefd);
		info->pipefd = NULL;
	}
	if (info->argv)
		safty_free(info->argv);
	dup2(g_signal.input_fd, 0);
	dup2(g_signal.output_fd, 1);
}

void	pipex(int argc, char **argv, t_environ **list)
{
	t_info	info;

	info_init(&info, argc, argv, *list);
	if (argv[0] == NULL)
	{
		finish(&info);
		return ;
	}
	if (g_signal.pipe_count == 0 && check_builtin(info.cmd[0]))
	{
		make_info_argv(&info, info.pipe_place[1], info.pipe_place[0]);
		if (check_redirect(&info) == 1)
		{
			g_signal.other_code = TRUE;
			g_signal.status = 1;
			finish(&info);
			return ;
		}
		do_builtin(info.argv[0], list, &info);
	}
	else
		multiple_pipes(&info, list);
	finish(&info);
}
