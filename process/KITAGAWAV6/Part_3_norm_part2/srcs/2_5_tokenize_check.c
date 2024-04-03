/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_5_tokenize_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:54:55 by yokitaga          #+#    #+#             */
/*   Updated: 2023/04/06 22:19:02 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort_no_tail_redirect(t_token **head, t_token *tmp, \
	t_token *current, t_token *prev)
{
	if (prev == NULL)
	{
		*head = current->next->next;
		if (tmp->next == NULL)
			current->next->next = NULL;
		else
			current->next->next = tmp->next;
		tmp->next = current;
	}
	else
	{
		prev->next = current->next->next;
		if (tmp->next == NULL)
			current->next->next = NULL;
		else
			current->next->next = tmp->next;
		tmp->next = current;
	}
}

void	norm_sort_with_tail_redirect(t_token **head, t_token *tmp, \
	t_token *current, t_token *tail_redirect)
{
	*head = tail_redirect->next->next;
	if (tmp->next == NULL)
		tail_redirect->next->next = NULL;
	else
		tail_redirect->next->next = tmp->next;
	tmp->next = current;
}

void	sort_with_tail_redirect(t_token **head, t_token *tmp, \
	t_token *current, t_token *prev)
{
	t_token	*tail_redirect;

	tail_redirect = current->next->next;
	while (check_redirect_token(tail_redirect) == true)
	{
		if (check_redirect_token(tail_redirect->next->next) == true)
			tail_redirect = tail_redirect->next->next;
		else
			break ;
	}
	if (prev == NULL)
		norm_sort_with_tail_redirect(head, tmp, current, tail_redirect);
	else
	{
		prev->next = tail_redirect->next->next;
		if (tmp->next == NULL)
			tail_redirect->next->next = NULL;
		else
			tail_redirect->next->next = tmp->next;
		tmp->next = current;
	}
}

int	norm_tmp_susumeru_1(t_token **tmp)
{
	while (*tmp != NULL && (*tmp)->next != NULL)
	{
		if ((*tmp)->next->next == NULL)
			return (0);
		*tmp = (*tmp)->next->next;
		if (check_redirect_token(*tmp) == false)
			break ;
	}
	if (*tmp == NULL)
		return (0);
	return (1);
}

void	norm_tmp_susumeru_2(t_token **tmp)
{
	while ((*tmp)->kind == TOKEN_WORD)
	{
		if ((*tmp)->next == NULL)
			break ;
		else if ((*tmp)->next->kind != TOKEN_WORD)
			break ;
		*tmp = (*tmp)->next;
	}
}
