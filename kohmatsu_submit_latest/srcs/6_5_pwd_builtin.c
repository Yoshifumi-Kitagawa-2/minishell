/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_5_pwd_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:55:33 by yokitaga          #+#    #+#             */
/*   Updated: 2023/03/31 18:43:14 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_builtin(t_info *info)
{
	char	*cwd;

	cwd = x_str_malloc(PATH_MAX);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		my_dprintf(1, "%s\n", cwd);
	else
	{
		while (info->list != NULL)
		{
			if (ft_strcmp(info->list->key, "PWD") == 0)
			{
				write(1, info->list->value, ft_strlen(info->list->value));
				write(1, "\n", 1);
				break ;
			}
			info->list = info->list->next;
		}
	}
	free(cwd);
}
