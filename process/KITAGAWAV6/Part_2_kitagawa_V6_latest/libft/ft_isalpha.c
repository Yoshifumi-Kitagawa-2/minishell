/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:02:15 by kohmatsu          #+#    #+#             */
/*   Updated: 2022/10/18 14:32:32 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'));
}

// #include <stdio.h>
// #include <ctype.h>
// int main(void)
// {
// 	int a = 'a';
// 	printf("%d\n", ft_isalpha(a));
// 	printf("%d", isalpha(a));
// 	return (0);
// }