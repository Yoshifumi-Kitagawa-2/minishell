/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:08:19 by matsushimak       #+#    #+#             */
/*   Updated: 2022/10/18 14:32:42 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long tmp)
{
	int	count;

	count = 0;
	while (tmp != 0)
	{
		tmp /= 10;
		count++;
	}
	return (count);
}

static void	do_it(long tmp, char *ret, int count, int *cycle)
{
	long	s1;
	long	s2;
	char	c;

	s1 = tmp / 10;
	s2 = tmp % 10;
	if (s1 != 0)
	{
		do_it(s1, ret, count, cycle);
		ret += *cycle;
	}
	c = s2 + '0';
	*ret = c;
	*cycle += 1;
	if (count == *cycle)
		*(++ret) = '\0';
}

char	*ft_itoa(int n)
{
	long	tmp;
	int		count;
	char	*ret;
	int		cycle;

	cycle = 0;
	tmp = n;
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
		tmp = -tmp;
	count = count_digits(tmp);
	if (n < 0)
		ret = (char *)malloc(sizeof(char) * (count + 2));
	else
		ret = (char *)malloc(sizeof(char) * (count + 1));
	if (!ret)
		return (0);
	if (n < 0)
		*ret++ = '-';
	do_it(tmp, ret, count, &cycle);
	if (n < 0)
		return (ret - 1);
	return (ret);
}

// #include <stdio.h>
// int main(void)
// {
// 	// int n = 2147483647;
// 	printf("%s\n", ft_itoa(0));
// 	return (0);
// }