/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:40:01 by kohmatsu          #+#    #+#             */
/*   Updated: 2022/11/09 18:57:20 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
	}
}

// #include <stdio.h>
// int main(void)
// {
// 	t_list *l = NULL;
// 	ft_lstadd_back(&l, ft_lstnew((void*)1));
// 	ft_lstadd_back(&l, ft_lstnew((void*)2));
// 	printf("%p\n", ft_lstlast(l)->next);
// 	return (0);
// }
