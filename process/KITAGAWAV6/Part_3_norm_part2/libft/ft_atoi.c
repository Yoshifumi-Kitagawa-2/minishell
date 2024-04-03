/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:07:43 by matsushimak       #+#    #+#             */
/*   Updated: 2023/03/30 23:38:30 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	overflow(long i, char str, int minus)
{
	int	digit;

	digit = str - '0';
	if (minus == 1)
		if ((i >= 922337203685477580 && digit > 7)
			|| (i >= 922337203685477581))
			return (-1);
	if (minus == -1)
		if ((i >= 922337203685477580 && digit > 8)
			|| (i >= 922337203685477581))
			return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int		minus;
	long	i;
	int		check;

	minus = 1;
	i = 0;
	while (('\t' <= *str && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		check = overflow(i, *str, minus);
		if (check != 1)
			return (check);
		i = i * 10 + (*str - '0');
		str++;
	}
	return (i * minus);
}

// #include <stdio.h>
// #include <stdlib.h>
// int main(void)
// {
// 	// printf("%ld", LONG_MAX);
// 	printf("%d\n", atoi("9223372036854775808"));
// 	return (0);
// }