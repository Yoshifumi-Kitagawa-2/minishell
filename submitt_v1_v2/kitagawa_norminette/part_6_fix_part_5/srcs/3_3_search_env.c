/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_3_search_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 13:27:36 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/14 21:03:41 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 == *str2)
	{
		if (*str1 == '\0' || *str2 == '\0')
			break ;
		str1++;
		str2++;
	}
	if (*str1 == '\0' && *str2 == '\0')
		return (0);
	else
		return (*str1 - *str2);
}

char	*search_env(char *key, t_environ *list)
{
	while (list != NULL)
	{
		if (ft_strcmp(list->key, key) == 0)
		{
			if (list->value != NULL)
				return (list->value);
			else
				return ("");
		}
		list = list->next;
	}
	return (NULL);
}
