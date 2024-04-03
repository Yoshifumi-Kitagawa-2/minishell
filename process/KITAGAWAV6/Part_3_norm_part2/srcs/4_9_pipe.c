/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_9_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:36:41 by yokitaga          #+#    #+#             */
/*   Updated: 2023/04/06 22:38:19 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	norm_execute_check_equal(char *key, t_info *info, int j)
{
	key = ft_strndup(info->argv[j], ft_strchr_index(info->argv[0], '='));
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

void	execute_check_equal(t_info *info, int j)
{
	char	*key;

	key = NULL;
	if (ft_strchr_index(info->argv[0], '=') == -1)
	{
		if (info->argv[0][0] == '/' || !(ft_strcmp(info->argv[0], "./")))
			err_exit(info->argv[0], "is a directory");
		else if (ft_strchr(info->argv[0], '/'))
		{
			if (access(info->argv[0], X_OK) != 0)
			{
				my_dprintf(2, "minishell: %s: Permission denied\n", \
					info->argv[0]);
				exit(126);
			}
			file_not_found(info->argv[0]);
			exit(127);
		}
		command_not_found(info->argv[0]);
	}
	else
		norm_execute_check_equal(key, info, j);
}
