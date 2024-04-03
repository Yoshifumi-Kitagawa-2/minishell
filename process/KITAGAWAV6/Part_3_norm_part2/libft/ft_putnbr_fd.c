/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:17:32 by kohmatsu          #+#    #+#             */
/*   Updated: 2022/10/18 14:33:29 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	tmp;
	int		s1;
	int		s2;
	char	c;

	tmp = n;
	if (tmp < 0)
	{
		write(fd, "-", 1);
		tmp = -tmp;
	}
	s1 = tmp / 10;
	s2 = tmp % 10;
	if (s1 != 0)
		ft_putnbr_fd(s1, fd);
	c = s2 + '0';
	write(fd, &c, 1);
}

// #include <stdio.h>
// int main(void)
// {
// 	int fd = 1;
// 	int n = -1;

// 	ft_putnbr_fd(n, fd);
// 	return (0);
// }