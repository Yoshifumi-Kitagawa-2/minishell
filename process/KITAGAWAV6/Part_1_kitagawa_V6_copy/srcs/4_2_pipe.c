/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_2_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:28:05 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/20 16:15:11 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	safty_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	malloc_error_free(int **pipefd, int i)
{
	while (i >= 0)
	{
		free(pipefd[i]);
		i--;
	}
	free(pipefd);
	pipefd = NULL;
}

int	count_list_len(t_environ *list)
{
	int	count;

	count = 0;
	while (list != NULL)
	{
		count++;
		list = list->next;
	}
	return (count);
}

char	**list_to_array(t_environ *list)
{
	char	**ret;
	char	*tmp;
	int		i;

	i = 0;
	ret = x_double_str_malloc(count_list_len(list) + 1);
	while (list != NULL)
	{
		if (ft_strcmp(list->value, "\\") != 0)
		{
			tmp = ft_strjoin(list->key, "=");
			ret[i] = ft_strjoin(tmp, list->value);
			free(tmp);
			i++;
		}
		list = list->next;
	}
	ret[i] = NULL;
	return (ret);
}

char	*make_exepath(char *path, char *command)
{
	char	*exe_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	exe_path = ft_strjoin(tmp, command);
	free(tmp);
	return (exe_path);
}
