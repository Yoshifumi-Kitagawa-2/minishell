/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:59:13 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/01/18 12:59:44 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			new->next = *lst;
			*lst = new;
		}
	}
}

// #include <stdio.h>
// int main(void)
// {
// 	t_list *lst = NULL;
// 	t_list *lst_new1 = ft_lstnew("hello");
// 	t_list *lst_new2 = ft_lstnew("konnnitiwa");
// 	ft_lstadd_front(&lst, lst_new1);
// 	ft_lstadd_front(&lst, lst_new2);
// 	printf("%s\n", lst->content);
// 	printf("%s\n", lst->next->content);
// 	return (0);
// }