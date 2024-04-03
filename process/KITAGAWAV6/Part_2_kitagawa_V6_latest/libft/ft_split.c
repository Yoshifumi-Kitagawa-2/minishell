/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:55:55 by matsushimak       #+#    #+#             */
/*   Updated: 2023/01/18 12:11:02 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_sep(char const *s, char c)
{
	int	amount;
	int	count;

	amount = 0;
	count = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (amount != 0)
				count++;
			amount = 0;
		}
		else
			amount++;
		s++;
	}
	if (amount != 0)
		return (count + 1);
	return (count);
}

static int	check(char **ans, size_t i)
{
	if (ans[i] == NULL)
	{
		while (i >= 0)
		{
			free(ans[i]);
			i--;
		}
		free(ans);
		return (0);
	}
	return (1);
}

static char	**do_it(const char *s, char c, char **ans, size_t i)
{
	size_t	len;

	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			len = 0;
			while (*s && *s != c)
			{
				len++;
				s++;
			}
			ans[i] = ft_substr(s - len, 0, len);
			if (!check(ans, i))
				return (NULL);
			i++;
		}
	}
	ans[i] = NULL;
	return (ans);
}

char	**ft_split(char const *s, char c)
{
	char	**ans;

	if (s == NULL)
		return (NULL);
	ans = (char **)malloc(sizeof(char *) * (count_sep(s, c) + 1));
	if (!ans)
		return (NULL);
	ans = do_it(s, c, ans, 0);
	return (ans);
}

// #include <stdio.h>
// int main(void)
// {
// 	char **tab = ft_split("ab\0cd", '\0');
// 	printf("%s\n", tab[0]);
// 	return (0);
// }