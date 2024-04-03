/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:58:39 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/14 20:23:13 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**x_double_str_malloc(int num)
{
	char	**tmp;

	tmp = (char **)malloc(sizeof(char *) * num);
	if (tmp == NULL)
		function_error("malloc");
	return (tmp);
}

char	*x_str_malloc(int num)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * num);
	if (tmp == NULL)
		function_error("malloc");
	return (tmp);
}

char	*x_strdup(char *str)
{
	char	*tmp;

	tmp = ft_strdup(str);
	if (tmp == NULL)
		function_error("ft_strdup");
	return (tmp);
}

int	**x_double_int_malloc(int num)
{
	int	**tmp;

	tmp = (int **)malloc(sizeof(int *) * num);
	if (tmp == NULL)
		function_error("malloc");
	return (tmp);
}

int	*x_int_malloc(int num)
{
	int	*tmp;

	tmp = (int *)malloc(sizeof(int) * num);
	if (tmp == NULL)
		function_error("malloc");
	return (tmp);
}
