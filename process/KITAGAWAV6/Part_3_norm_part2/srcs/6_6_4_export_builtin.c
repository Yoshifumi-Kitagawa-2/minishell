/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_6_4_export_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:26:16 by yokitaga          #+#    #+#             */
/*   Updated: 2023/03/30 14:50:32 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	no_equal(char *arg, t_environ **list)
{
	char	*key;
	char	*value;

	key = ft_strdup(arg);
	if (key == NULL)
		function_error("strdup");
	value = ft_strdup("\\");
	list_add_back_export(list, key, value);
	free(key);
	free(value);
}

void	add_new_env(char *arg, t_environ **list)
{
	char	*key;
	char	*value;

	if (ft_strchr_index(arg, '=') == -1)
		no_equal(arg, list);
	else
	{
		key = ft_strndup(arg, ft_strchr_index(arg, '='));
		if (key == NULL)
			function_error("strndup");
		value = ft_substr(arg, ft_strchr_index(arg, '=') + 1,
				ft_strlen(arg) - ft_strchr_index(arg, '=') - 1);
		if (value == NULL)
			function_error("substr");
		list_add_back_export(list, key, value);
		free(key);
		free(value);
	}
}
