/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:55:05 by kohmatsu          #+#    #+#             */
/*   Updated: 2022/10/18 14:32:25 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

// #include <stdio.h>
// #include <strings.h>
// int main(void)
// {
// 	char s[] = "abcdefghi";
// 	bzero(s + 3, 0);
// 	printf("%s\n\n", s);

// 	char s1[] = "abcdefghi";
// 	ft_bzero(s1 + 3, 0);
// 	printf("%s\n\n", s1);
// }