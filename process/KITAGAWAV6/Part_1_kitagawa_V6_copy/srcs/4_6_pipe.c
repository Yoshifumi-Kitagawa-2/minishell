/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_6_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:30:42 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/04/04 02:07:02 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_fd(t_info *info, int i)
{
	int	j;

	j = 0;
	if (info->input_fd == 0)
	{
		if (i != 0)
			dup2(info->pipefd[i - 1][0], 0);
	}
	if (info->output_fd == 1)
	{
		if (i != g_signal.pipe_count)
			dup2(info->pipefd[i][1], 1);
	}
	while (j < g_signal.pipe_count)
	{
		close(info->pipefd[j][0]);
		close(info->pipefd[j][1]);
		j++;
	}
}

void	check_equal(t_info *info, int *j)
{
	char	*key;

	while (info->argv[*j] != NULL)
	{
		if (ft_strchr_index(info->argv[*j], '=') == -1)
			break ;
		else
		{
			key = ft_strndup(info->argv[*j],
					ft_strchr_index(info->argv[*j], '='));
			if (search_env(key, info->list) != NULL)
			{
				free(key);
				break ;
			}
			else
			{
				free(key);
				*j += 1;
			}
		}
	}
}

void	do_builtin(char *argv, t_environ **list, t_info *info)
{
	if (ft_strcmp(argv, "cd") == 0)
		cd_builtin(info);
	else if (ft_strcmp(argv, "echo") == 0)
		echo_builtin(info, 0);
	else if (ft_strcmp(argv, "exit") == 0)
		exit_builtin(info);
	else if (ft_strcmp(argv, "unset") == 0)
		unset_builtin(info, list);
	else if (ft_strcmp(argv, "env") == 0)
		env_builtin(info);
	else if (ft_strcmp(argv, "export") == 0)
		export_builtin(info, list);
	else if (ft_strcmp(argv, "pwd") == 0)
		pwd_builtin(info);
}

void	do_mix_builtin(t_info *info, t_environ **list, int i)
{
	if (ft_strcmp(info->cmd[info->pipe_place[i] + 1], "env") == 0)
		env_builtin(info);
	else if (ft_strcmp(info->cmd[info->pipe_place[i] + 1],
			"export") == 0)
		export_builtin(info, list);
	else if (ft_strcmp(info->cmd[info->pipe_place[i] + 1],
			"pwd") == 0)
		pwd_builtin(info);
	else if (ft_strcmp(info->cmd[info->pipe_place[i] + 1],
			"echo") == 0)
		echo_builtin(info, 0);
}

char	*create_path(t_info *info, int j)
{
	char	*exe_path;
	int		index;

	exe_path = NULL;
	index = 0;
	if (access(exe_path, X_OK) == 0 && ft_strcmp(exe_path, "./"))
		err_exit(info->argv[j], "command not found");
	if (info->path == NULL && path_null(info->argv[j]) == true)
		return (info->argv[j]);
	while ((info->path)[index] != NULL && access(exe_path, X_OK))
	{
		if (ft_strchr(info->argv[j], '/') == NULL)
			exe_path = make_exepath((info->path)[index],
					(info->argv)[j]);
		else
			exe_path = info->argv[j];
		index++;
	}
	index = 0;
	while (index != j)
	{
		info->argv++;
		index++;
	}
	return (exe_path);
}
