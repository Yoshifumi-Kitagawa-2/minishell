/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:32:33 by kohmatsu          #+#    #+#             */
/*   Updated: 2022/10/18 14:33:20 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (d >= s)
	{
		d += (len - 1);
		s += (len - 1);
		while (len--)
			*d-- = *s--;
	}
	else
	{
		while (len--)
			*d++ = *s++;
	}
	return (dst);
}

// #include        <stdio.h>
// #include        <string.h>
// int main(void)
// {
// 	char str[] = "abcdefghijklmnopqrstu";
// 	printf("移動前：%s\n",str);
// 	memmove(str+5, str, 10);        /* 重複エリアのコピー */
// 	printf("移動後：%s\n\n",str);

// 	char str1[] = "abcdefghijklmnopqrstu";
// 	printf("移動前：%s\n",str1);
// 	ft_memmove(str1+5, str1, 10);        /* 重複エリアのコピー */
// 	printf("移動後：%s\n",str1);
//         return 0;
// }