/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_5_tokenize_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:54:55 by yokitaga          #+#    #+#             */
/*   Updated: 2023/04/06 18:39:40 by yokitaga         ###   ########.fr       */
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

void	sort(t_token **head, t_token *tmp, t_token *current, \
	t_token *prev, t_token *tail_redirect)
{
	if (tail_redirect == NULL)
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
	else
	{
		if (prev == NULL)
		{
			*head = tail_redirect->next->next;
			if (tmp->next == NULL)
				tail_redirect->next->next = NULL;
			else
				tail_redirect->next->next = tmp->next;
			tmp->next = current;
		}
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
}

int	check_sort_or_not(t_token **head, t_token *tmp,
	t_token *current, t_token *prev)
{
	t_token	*tail_redirect;

	tail_redirect = NULL;
	if (current->next == NULL || current->next->kind != TOKEN_WORD)
	{
		tokenize_error_2("unexpected token", current->word);
		return (1);
	}
	else
	{
		tmp = current->next->next;
		if (tmp == NULL || (tmp->kind != TOKEN_WORD \
			&& tmp->kind != TOKEN_METACHAR))
			;
		else
		{
			if (check_redirect_token(tmp) == true)
			{
				tail_redirect = current;
				while (tmp != NULL && tmp->next != NULL)
				{
					if (tmp->next->next == NULL)
						return (0);
					if (check_redirect_token(tmp->next->next) == true)
					{
						tmp = tmp->next->next;
						tail_redirect = tmp;
					}
					else
					{
						tmp = tmp->next->next;
						break ;
					}
				}
				if (tmp == NULL)
					return (0);
			}
			if (tmp->kind == TOKEN_WORD)
			{
				while (tmp->kind == TOKEN_WORD)
				{
					if (tmp->next == NULL)
						break ;
					else if (tmp->next->kind != TOKEN_WORD)
						break ;
					tmp = tmp->next;
				}
			}
			sort(head, tmp, current, prev, tail_redirect);
		}
	}
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
