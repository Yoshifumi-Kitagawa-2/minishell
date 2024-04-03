/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_8_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:32:05 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/30 14:26:03 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipe(t_token *token)
{
	int	count;

	count = 0;
	while (token->kind != TOKEN_EOF)
	{
		if (token->word[0] == '|' && ft_strlen(token->word) == 1)
			count++;
		token = token->next;
	}
	return (count);
}

char	**make_path_list(t_environ *list)
{
	while (list != NULL)
	{
		if (ft_strcmp(list->key, "PATH") == 0)
			return (ft_split(list->value, ':'));
		list = list->next;
	}
	return (NULL);
}

void	open_pipefd(t_info *info)
{
	int	i;

	info->pipefd = x_double_int_malloc(g_signal.pipe_count);
	i = 0;
	while (i < g_signal.pipe_count)
	{
		info->pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (info->pipefd[i] == NULL)
		{
			malloc_error_free(info->pipefd, i);
			function_error("malloc");
		}
		i++;
	}
	i = 0;
	while (i < g_signal.pipe_count)
		pipe(info->pipefd[i++]);
}

int	*place_pipe(t_info *info)
{
	int	*ret;
	int	i;
	int	j;

	ret = x_int_malloc(g_signal.pipe_count + 2);
	ret[0] = -1;
	ret[g_signal.pipe_count + 1] = info->argc;
	i = 0;
	j = 1;
	while (i < info->argc)
	{
		if (info->cmd[i][0] == '|' && ft_strlen(info->cmd[i]) == 1
				&& info->cmd[i + 1] != NULL)
		{
			ret[j++] = i;
		}
		i++;
	}
	open_pipefd(info);
	return (ret);
}

bool	path_null(char *path)
{
	if (ft_strchr(path, '/') == NULL)
	{
		file_not_found(path);
		exit(127);
	}
	else
		return (true);
}
