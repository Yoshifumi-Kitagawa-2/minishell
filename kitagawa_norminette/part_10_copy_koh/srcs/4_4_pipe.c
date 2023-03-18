/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_4_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:29:48 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/15 20:49:27 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_splitable(t_info *info, int start, int end)
{
	int	count;
	int	i;

	count = 0;
	while (start < end)
	{
		if (ft_strchr(info->cmd[start], ' '))
		{
			i = 0;
			while (info->cmd[start][i] == ' ')
				i++;
			while (info->cmd[start][i])
			{
				if (info->cmd[start][i] == ' ')
					count++;
				i++;
			}
		}
		start++;
	}
	return (count);
}

void	remove_redirect(char **tmp, t_info *info, int i)
{
	int		argv_index;
	int		tmp_index;

	argv_index = 0;
	tmp_index = 0;
	if (!ft_strcmp(info->argv[0], "<") || !ft_strcmp(info->argv[0], ">"))
	{
		tmp = x_double_str_malloc(info->argv_count - 1);
		tmp[tmp_index++] = x_strdup("cat");
	}
	else
		tmp = x_double_str_malloc(info->argv_count - 2);
	while (argv_index != i)
		tmp[tmp_index++] = x_strdup(info->argv[argv_index++]);
	argv_index += 2;
	while (info->argv[argv_index])
		tmp[tmp_index++] = x_strdup(info->argv[argv_index++]);
	safty_free(info->argv);
	info->argv = tmp;
}

int	count_heredoc(char **argv)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "<<") == 0)
			count++;
		i++;
	}
	return (count);
}

int	detect_something(t_info *info, int i)
{
	if (*(info->argv)[i] == '<')
	{
		if (access(info->argv[i + 1], F_OK) == -1)
		{
			file_not_found(info->argv[i + 1]);
			return (1);
		}
	}
	else if (*(info->argv)[i] == '>')
	{
		if (ft_strchr(info->argv[i + 1], '$') != NULL)
		{
			ambiguous_redirect(info->argv[i + 1]);
			return (1);
		}
	}
	return (0);
}

int	check_redirect(t_info *info)
{
	int	i;
	int	heredoc_count;
	int	tmp;

	i = 0;
	heredoc_count = count_heredoc(info->argv);
	while ((info->argv)[i] != NULL)
	{
		tmp = branch_do_v1(info, i, heredoc_count);
		if (tmp == 1)
			return (1);
		else if (tmp == 2)
			continue ;
		i++;
	}
	return (0);
}
