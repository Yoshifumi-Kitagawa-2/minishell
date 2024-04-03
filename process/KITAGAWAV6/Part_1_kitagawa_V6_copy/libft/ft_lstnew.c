/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:35:57 by kohmatsu          #+#    #+#             */
/*   Updated: 2022/10/18 21:28:56 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ret;

	ret = (t_list *)malloc(sizeof(t_list));
	if (!ret)
		return (NULL);
	ret->content = content;
	ret->next = 0;
	return (ret);
}

// #include <stdio.h>
// int main(void)
// {
// 	t_list *l;
// 	l = ft_lstnew((void*)1);
// 	printf("%p\n", (l->content));
// 	return (0);
// }