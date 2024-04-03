/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_6_tokenize_check_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:13:38 by yokitaga          #+#    #+#             */
/*   Updated: 2023/04/06 22:19:53 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_redirect_token(t_token *token)
{
	if (token->kind == TOKEN_METACHAR)
	{
		if (ft_strcmp(token->word, ">") == 0 || \
			ft_strcmp(token->word, ">>") == 0 \
			|| ft_strcmp(token->word, "<") == 0 || \
				ft_strcmp(token->word, "<<") == 0)
			return (true);
	}
	return (false);
}

int	check_sort_or_not(t_token **head, t_token *tmp,
	t_token *current, t_token *prev)
{
	bool	tail_redirect;

	tail_redirect = false;
	if (current->next == NULL || current->next->kind != TOKEN_WORD)
	{
		tokenize_error_2("unexpected token", current->word);
		return (1);
	}
	tmp = current->next->next;
	if (tmp == NULL || (tmp->kind != TOKEN_WORD \
		&& tmp->kind != TOKEN_METACHAR))
		return (0);
	if (check_redirect_token(tmp) == true)
	{
		tail_redirect = true;
		if (norm_tmp_susumeru_1(&tmp) == 0)
			return (0);
	}
	if (tmp->kind == TOKEN_WORD)
		norm_tmp_susumeru_2(&tmp);
	if (tail_redirect == true)
		sort_with_tail_redirect(head, tmp, current, prev);
	else
		sort_no_tail_redirect(head, tmp, current, prev);
	return (0);
}

void	check_and_sort_tokens(t_token **head)
{
	t_token	*current;
	t_token	*prev;
	t_token	*tmp;

	current = *head;
	prev = NULL;
	tmp = NULL;
	while (current != NULL)
	{
		if (check_redirect_token(current) == true)
		{
			if (check_sort_or_not(head, tmp, current, prev))
				break ;
		}
		prev = current;
		current = current->next;
	}
}

void	check_pipe_place(t_token **head)
{
	t_token	*current;

	current = *head;
	if (current == NULL)
		return ;
	if (ft_strcmp(current->word, "|") == 0)
	{
		tokenize_error_2("unexpected token", current->word);
		return ;
	}
	while (current != NULL)
	{
		if (ft_strcmp(current->word, "|") == 0 && (current->next == NULL || \
			ft_strcmp(current->next->word, "|") == 0))
		{
			tokenize_error_2("unexpected token", current->word);
			return ;
		}
		current = current->next;
	}
}
