/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:32:40 by matsushimak       #+#    #+#             */
/*   Updated: 2022/10/23 23:18:29 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*tmp1;
	char	*tmp2;
	size_t	i;

	tmp1 = (char *)haystack;
	if (*needle == '\0')
		return (tmp1);
	if (haystack == NULL && needle != NULL && len == 0)
		return (NULL);
	while (*tmp1 && len)
	{
		tmp2 = (char *)needle;
		i = tmp2 - needle;
		while (*(tmp1 + i) && *tmp2 && *(tmp1 + i) == *tmp2 && i < len)
		{
			tmp2++;
			i++;
		}
		if (i == ft_strlen(needle))
			return (tmp1);
		tmp1++;
		len--;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	printf("%s\n", ft_strnstr(NULL, "aiueo", 5));
// 	return (0);
// }