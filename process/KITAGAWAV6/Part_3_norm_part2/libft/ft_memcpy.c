/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:32:29 by kohmatsu          #+#    #+#             */
/*   Updated: 2022/12/07 13:34:17 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ans;

	ans = (unsigned char *)dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n--)
	{
		*ans = *(unsigned char *)src;
		ans++;
		src++;
	}
	return (dst);
}

// #include        <stdio.h>
// #include        <string.h>
// int main(void)
// {
// 	char str1[128] = {1,1,1,1,1,1,1};
// 	char str2[] = "ab\0cde";        /* 途中に空文字のある文字列 */
// 	int i;
// 	printf("コピー前　中身の確認\n");
// 	for (i=0; i<15; i++)
// 			printf("%#x ",str1[i]);
// 	printf("\n");
// 	memcpy(0, 0, 10);
// 	printf("コピー後　中身の確認\n");
// 	for (i=0; i<15; i++)
// 			printf("%#x ",str1[i]);
// 	printf("\n\n");

// 	char str11[128] = {1,1,1,1,1,1,1};
// 	char str22[] = "ab\0cde";        /* 途中に空文字のある文字列 */
// 	int j;
// 	printf("コピー前　中身の確認\n");
// 	for (j=0; j<15; j++)
// 			printf("%#x ",str11[j]);
// 	printf("\n");
// 	ft_memcpy(0, 0, 10);
// 	printf("コピー後　中身の確認\n");
// 	for (j=0; j<15; j++)
// 			printf("%#x ",str11[j]);
// 	printf("\n");
//         return 0;
// }