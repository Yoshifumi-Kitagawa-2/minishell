/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_2_env_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:26:14 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/04/01 15:51:06 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	output_env(t_environ *tmp)
{
	ft_putstr_fd(tmp->key, STDOUT);
	write(1, "=", 1);
	if (tmp->value != NULL)
		ft_putstr_fd(tmp->value, STDOUT);
	write(1, "\n", 1);
}

void	env_builtin(t_info *info)
{
	t_environ	*tmp;

	tmp = info->list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "COPYPWD") == 0)
		{
			tmp = tmp->next;
			continue ;
		}
		else if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			if (ft_strcmp(tmp->value, "") == 0)
			{
				tmp = tmp->next;
				continue ;
			}
		}
		if (ft_strcmp(tmp->value, "\\") != 0)
			output_env(tmp);
		tmp = tmp->next;
	}
}
