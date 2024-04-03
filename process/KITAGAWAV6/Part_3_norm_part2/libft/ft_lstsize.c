/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:11:37 by kohmatsu          #+#    #+#             */
/*   Updated: 2022/10/18 21:22:07 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;

	count = 0;
	if (lst == NULL)
		return (0);
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

// #include <stdio.h>
// int main(void)
// {
// 	t_list *l = NULL;
// 	ft_lstadd_front(&l, ft_lstnew((void *)1));
// 	ft_lstadd_front(&l, ft_lstnew((void *)1));
// 	ft_lstadd_front(&l, ft_lstnew((void *)1));
// 	printf("%d\n", ft_lstsize(l));
// 	return (0);
// }
