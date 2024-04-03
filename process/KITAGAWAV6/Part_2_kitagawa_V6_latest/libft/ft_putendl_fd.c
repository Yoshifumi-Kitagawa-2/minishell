/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:13:41 by kohmatsu          #+#    #+#             */
/*   Updated: 2022/10/23 23:04:28 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	if (s != NULL)
		write(fd, "\n", 1);
}

// #include <stdio.h>
// int main(void)
// {
// 	int fd = 1;
// 	char *s = "abc";
// 	ft_putendl_fd(s, fd);
// 	return (0);
// }