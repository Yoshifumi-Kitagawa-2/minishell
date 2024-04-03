/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:03:15 by kohmatsu          #+#    #+#             */
/*   Updated: 2022/10/18 21:52:04 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	void	*ans;

	ans = (unsigned char *)s;
	while (n--)
	{
		if (*(unsigned char *)ans == (unsigned char)c)
			return (ans);
		ans++;
	}
	return (NULL);
}

// #include        <stdio.h>
// #include        <string.h>

// int main(void)
// {
//         char str[] = "abcdef\0ghij";    /* 途中に空文字のある文字列 */
//         char *p;
//         p = ft_memchr(str, 'h', 12);
//         printf("検索文字は文字列の%ld番目\n\n",p - str);
// 		char str1[] = "abcdef\0ghij";    /* 途中に空文字のある文字列 */
//         char *q;
//         q = memchr(str1, 'h', 12);
//         printf("検索文字は文字列の%ld番目\n",q - str1);
//         return 0;
// }