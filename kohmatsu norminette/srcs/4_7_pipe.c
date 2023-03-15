/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_7_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:31:21 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/15 00:17:39 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_check_equal(t_info *info, int j)
{
	char	*key;

	if (ft_strchr_index(info->argv[0], '=') == -1)
		command_not_found(info->argv[0]);
	else
	{
		key = ft_strndup(info->argv[j],
				ft_strchr_index(info->argv[0], '='));
		if (search_env(key, info->list) != NULL)
		{
			free(key);
			command_not_found(info->argv[0]);
		}
		else
		{
			free(key);
			exit(0);
		}
	}
}

void	child_do(char *exe_path, t_info *info, int i, t_environ *list)
{
	int	j;

	j = 0;
	set_signal_child();
	make_info_argv(info, info->pipe_place[i + 1], info->pipe_place[i]);
	if (check_redirect(info) == 1)
		exit(1);
	do_fd(info, i);
	j = 0;
	check_equal(info, &j);
	if (check_builtin(info->cmd[info->pipe_place[i] + 1]))
	{
		if (i > g_signal.pipe_count - 1)
			do_builtin(info->cmd[info->pipe_place[i] + 1], list, info);
		else
			do_mix_builtin(info, list, i);
		exit(0);
	}
	else
	{
		exe_path = create_path(info, j);
		if (execve(exe_path, info->argv,
				list_to_array(info->list)) == -1)
			execute_check_equal(info, j);
	}
}

void	parent_do(int i, t_info *info)
{
	set_signal_parent();
	if (i > 0)
	{
		close(info->pipefd[i - 1][0]);
		close(info->pipefd[i - 1][1]);
	}
}

void	waiting(void)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < g_signal.pipe_count + 1)
	{
		wait(&wstatus);
		i++;
	}
	if (wstatus == SIGINT)
		write(1, "\n", 1);
	else if (wstatus == SIGQUIT)
		write(1, "QUIT: 3\n", 8);
	if (wstatus == SIGINT || wstatus == SIGQUIT)
	{
		g_signal.status = 128 + wstatus;
		g_signal.other_code = TRUE;
	}
	else
	{
		g_signal.status = WEXITSTATUS(wstatus);
		g_signal.other_code = TRUE;
	}
}

void	multiple_pipes(t_info *info, t_environ *list)
{
	int		i;
	pid_t	pid;
	char	*exe_path;

	i = 0;
	exe_path = NULL;
	while (i < g_signal.pipe_count + 1)
	{
		pid = fork();
		if (pid == -1)
			function_error("fork");
		else if (pid == 0)
			child_do(exe_path, info, i, list);
		else
			parent_do(i, info);
		i++;
	}
	waiting();
}
