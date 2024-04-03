/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_3_echo_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:07:12 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/31 18:31:38 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_until_doll(char *str)
{
	int	j;

	j = 0;
	while (str[j] != '$')
	{
		write(1, &str[j], 1);
		j++;
	}
}

void	no_option(t_info *info, int j)
{
	int	i;

	i = j + 1;
	while (info->argv[i])
	{
		if (ft_strchr(info->argv[i], '$') == NULL)
		{
			if (info->argv[i] != NULL)
				ft_putstr_fd(info->argv[i], STDOUT);
		}
		else if (g_signal.not_expand_flag == 1)
			ft_putstr_fd(info->argv[i], STDOUT);
		else
			write_until_doll(info->argv[i]);
		if (info->argv[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	option(t_info *info, int j)
{
	int	i;

	i = j + 2;
	while (info->argv[i] != NULL && ft_strcmp(info->argv[i], "-n") == 0)
		i++;
	while (info->argv[i])
	{
		if (ft_strchr(info->argv[i], '$') == NULL)
		{
			if (info->argv[i] != NULL)
				ft_putstr_fd(info->argv[i], STDOUT);
		}
		else if (g_signal.not_expand_flag == 1)
			ft_putstr_fd(info->argv[i], STDOUT);
		else
			write_until_doll(info->argv[i]);
		if (info->argv[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

bool	compare_option(char *str)
{
	int	i;

	if (ft_strcmp(str, "-n") == 0)
		return (true);
	else if (ft_strncmp(str, "-n", 2) == 0)
	{
		i = 2;
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (false);
			i++;
		}
		return (true);
	}
	else
		return (false);
}

void	echo_builtin(t_info *info, int j)
{
	int	option_flag;

	option_flag = 0;
	if (compare_option(info->argv[1]) == true)
		option_flag = 1;
	if (option_flag == 0)
		no_option(info, j);
	else
		option(info, j);
}
