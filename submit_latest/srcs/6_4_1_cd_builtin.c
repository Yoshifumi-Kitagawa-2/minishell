/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_4_1_cd_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:23:51 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/04/01 16:30:42 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_old_and_new_pwd(t_info *info)
{
	char	new_pwd[PATH_MAX];
	char	*error_pwd;

	if (getcwd(new_pwd, sizeof(new_pwd)) != NULL)
		check_private(new_pwd, info);
	else
	{
		while (info->list != NULL)
		{
			if (ft_strcmp(info->list->key, "PWD") == 0)
			{
				error_pwd = ft_strjoin_with_free(info->list->value, "/.", 1);
				info->list->value = error_pwd;
				break ;
			}
			info->list = info->list->next;
		}
		perror("cd: error retrieving current directory: \
getcwd: cannot access parent directories");
	}
}

void	do_no_argv(t_info *info)
{
	char	*home;

	home = ft_strdup(search_env("HOME", info->list));
	if (home == NULL)
	{
		my_dprintf(STDERR_FILENO, "minishell: cd: HOME not set\n");
		g_signal.status = 1;
		g_signal.other_code = TRUE;
	}
	else if ((chdir(home)) == -1)
	{
		if (ft_strcmp(search_env("HOME", info->list), "") != 0)
		{
			my_dprintf(STDERR_FILENO, "minishell: cd: %s:\
	No such file or directory\n", search_env("HOME", info->list));
			g_signal.status = 1;
			g_signal.other_code = TRUE;
		}
	}
	free(home);
}

void	cd_minus(t_info *info)
{
	if (ft_strcmp(search_env("OLDPWD", info->list), "\\") == 0)
	{
		my_dprintf(STDERR_FILENO, "minishell: cd: OLDPWD not set\n");
		g_signal.status = 1;
		g_signal.other_code = TRUE;
	}
	else
	{
		my_dprintf(STDOUT_FILENO, "%s\n", search_env("OLDPWD", info->list));
		if (chdir(search_env("OLDPWD", info->list)) == -1)
		{
			my_dprintf(STDERR_FILENO, "minishell: cd: %s:\
No such file or directory\n", search_env("OLDPWD", info->list));
			g_signal.status = 1;
			g_signal.other_code = TRUE;
		}
	}
}

void	cd_builtin(t_info *info)
{
	if (info->argv[1] == NULL)
		do_no_argv(info);
	else
	{
		if (info->argv[1][0] == '-')
		{
			if (info->argv[1][1] == '\0')
				cd_minus(info);
			else if (info->argv[1][1] == '-')
				do_no_argv(info);
			else
				my_dprintf(STDERR_FILENO, "minishell: cd: -%s: invalid option\n",
					info->argv[1]);
		}
		else if (chdir(info->argv[1]) == -1)
		{
			my_dprintf(STDERR_FILENO, "minishell: cd:%s:\
No such file or directory\n", info->argv[1]);
			g_signal.status = 1;
			g_signal.other_code = TRUE;
		}
	}
	get_old_and_new_pwd(info);
}
