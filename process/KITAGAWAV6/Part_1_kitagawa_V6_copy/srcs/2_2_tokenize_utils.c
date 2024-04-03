/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_2_tokenize_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:51:03 by yokitaga          #+#    #+#             */
/*   Updated: 2023/03/18 11:22:49 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_blank(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (true);
	else
		return (false);
}

bool	is_metacharacter(char c)
{
	if (c != 0 && ft_strchr("|&;()<> \t\n", c) != NULL)
		return (true);
	else
		return (false);
}

bool	is_control_operator(char *s)
{
	static char	*control_operators[9] = \
		{"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t		i;

	i = 0;
	while (i < 9)
	{
		if (ft_strcmp(s, control_operators[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

t_token	*new_token(t_token_kind kind)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		function_error("malloc");
	new_token->kind = kind;
	new_token->word = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	append_token(t_token **head, t_token *new)
{
	t_token	*current;

	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}
