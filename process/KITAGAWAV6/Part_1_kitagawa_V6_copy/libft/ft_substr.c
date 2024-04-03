/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:57:45 by matsushimak       #+#    #+#             */
/*   Updated: 2022/10/19 20:47:54 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	tmp;

	tmp = len;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_calloc(1, 1));
	if (ft_strlen(s + start) < len)
		tmp = ft_strlen(s + start);
	ret = (char *)malloc(sizeof(char) * (tmp + 1));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s + start, tmp + 1);
	return (ret);
}

// #include <stdio.h>
// int main(void)
// {
// 	char *s = "libft-test-tokyo";
// 	printf("%s\n", ft_substr(s, 20, 100));
// 	printf("");
// 	return (0);
// }