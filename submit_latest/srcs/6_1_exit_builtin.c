/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_1_exit_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:53:49 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/31 00:07:37 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_exit(char *str)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	g_signal.status = 255;
	exit(255);
}

int	checking(t_info *info)
{
	if ((ft_atoi(info->argv[1]) == -1 && ft_strcmp(info->argv[1], "-1")
			&& ft_strcmp(info->argv[1], "9223372036854775807")))
		return (1);
	if ((ft_atoi(info->argv[1]) == 0 && ft_strcmp(info->argv[1], "0")
			&& ft_strcmp(info->argv[1], "-9223372036854775808")))
		return (1);
	return (0);
}

void	exit_tmp(t_info *info)
{
	int	i;

	i = 0;
	while (info->argv[1][i])
	{
		if (ft_isdigit(info->argv[1][i]) == 0 && info->argv[1][i] != '-')
			error_exit(info->argv[1]);
		i++;
	}
	if (checking(info))
		error_exit(info->argv[1]);
	if (info->argv[2] != NULL)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		g_signal.status = 1;
		g_signal.other_code = TRUE;
		return ;
	}
}

void	exit_builtin(t_info *info)
{
	int	status_code;

	status_code = 0;
	if (info->argv[1] != NULL)
	{
		exit_tmp(info);
		if (info->argv[2] != NULL)
			return ;
		status_code = ft_atoi(info->argv[1]);
		g_signal.status = status_code;
	}
	else
		status_code = g_signal.status;
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(status_code);
}
