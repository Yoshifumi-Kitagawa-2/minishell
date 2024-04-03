/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:35:57 by kohmatsu          #+#    #+#             */
/*   Updated: 2022/10/21 13:19:19 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	if (n == 0)
		return (0);
	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	while (n)
	{
		if (*tmp1 != *tmp2)
			return ((*tmp1 - *tmp2));
		tmp1++;
		tmp2++;
		n--;
	}
	return (0);
}

// #include        <stdio.h>
// #include        <string.h>

// int main(void)
// {
// 	printf("%d\n", memcmp(NULL, NULL, 0));
// 	return (0);
// }