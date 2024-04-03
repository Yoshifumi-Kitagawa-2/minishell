/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:16:58 by matsushimak       #+#    #+#             */
/*   Updated: 2022/11/07 12:26:15 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*domain;

	if (count == 0 || size == 0)
		return (ft_calloc(1, 1));
	if (SIZE_MAX / size < count)
		return (NULL);
	else
	{
		domain = malloc(count * size);
		if (!domain)
			return (NULL);
		ft_bzero(domain, (count * size));
		return (domain);
	}
}

// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
// 	printf("%s\n", (char *)ft_calloc(0, 0));
// 	printf("%s\n", (char *)calloc(0, 0));
// 	// printf("%zu\n", SIZE_MAX);
// 	return (0);
// }   