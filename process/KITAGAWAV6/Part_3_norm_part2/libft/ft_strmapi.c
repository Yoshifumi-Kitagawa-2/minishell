/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:51:07 by matsushimak       #+#    #+#             */
/*   Updated: 2022/10/23 23:04:55 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ret;
	char			*lead;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ret)
		return (NULL);
	lead = ret;
	while (*s)
	{
		*ret = f(i, *s);
		i++;
		ret++;
		s++;
	}
	*ret = '\0';
	return (lead);
}

// char conv(unsigned int i, char c)
// {
// 	(void)i;
// 	return (c -= 32);
// }

// #include <stdio.h>
// int main(void)
// {
// 	char *s = "abc";
// 	printf("%s\n",ft_strmapi(s, conv));
// 	return (0);
// }