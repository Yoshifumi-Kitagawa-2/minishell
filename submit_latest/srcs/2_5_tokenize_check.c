/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_5_tokenize_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:54:55 by yokitaga          #+#    #+#             */
/*   Updated: 2023/04/05 11:36:21 by kohmatsu         ###   ########.fr       */
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

void	sort(t_token **head, t_token *tmp, t_token *current, t_token *prev)
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

int	check_sort_or_not(t_token **head, t_token *tmp,
	t_token *current, t_token *prev)
{
	if (current->next == NULL || current->next->kind != TOKEN_WORD)
	{
		tokenize_error_2("unexpected token", current->word);
		return (1);
	}
	else
	{
		tmp = current->next->next;
		if (tmp == NULL || tmp->kind != TOKEN_WORD)
			;
		else
		{
			while (tmp->kind == TOKEN_WORD)
			{
				if (tmp->next == NULL || tmp->next->kind != TOKEN_WORD)
					break ;
				tmp = tmp->next;
			}
			sort(head, tmp, current, prev);
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
