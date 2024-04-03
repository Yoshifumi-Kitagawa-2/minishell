/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:48:54 by kohmatsu          #+#    #+#             */
/*   Updated: 2022/10/18 21:19:17 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}

// #include <stdio.h>
// int main(void)
// {
// 	t_list *l=NULL;
// 	ft_lstadd_back(&l, ft_lstnew((void *)1));
// 	ft_lstadd_back(&l, ft_lstnew((void *)2));
// 	printf("%p\n",l->content);
// 	ft_lstdelone(l, free);
// 	printf("%p\n",l->content);
// 	return (0);
// }