/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:51:16 by kohmatsu          #+#    #+#             */
/*   Updated: 2022/10/19 19:27:36 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (lst && del)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = tmp;
		}
		lst = NULL;
	}
}

// #include <stdio.h>
// int main(void)
// {
// 	t_list *l = NULL;
// 	ft_lstadd_back(&l, ft_lstnew((void *)1));
// 	ft_lstadd_back(&l, ft_lstnew((void *)2));
// 	ft_lstclear(&l, free);
// 	printf("%p\n", l->next);
// 	return (0)
// }
