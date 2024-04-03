/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_3_tokenize_handles.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:54:10 by yokitaga          #+#    #+#             */
/*   Updated: 2023/03/18 11:24:39 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*handle_metacharacter(char **rest, char *line)
{
	t_token		*token;
	static char	*metacharacters[9] = \
		{">>", "<<", "|", "&", ";", "(", ")", "<", ">"};
	size_t		i;
	char		*metachar;

	i = 0;
	token = new_token(TOKEN_METACHAR);
	while (i < 9)
	{
		if (ft_strncmp(line, metacharacters[i], \
			ft_strlen(metacharacters[i])) == 0)
		{
			metachar = ft_strdup(metacharacters[i]);
			if (metachar == NULL)
				function_error("strdup");
			*rest = line + ft_strlen(metachar);
			token->word = metachar;
			return (token);
		}
		i++;
	}
	assert_error("Unexpected operator");
	return (NULL);
}

t_token	*handle_contorol_op(char **rest, char *line)
{
	t_token		*token;
	static char	*control_operators[9] = \
		{"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t		i;
	char		*op;

	i = 0;
	token = new_token(TOKEN_CONTROL_OP);
	while (i < 9)
	{
		if (ft_strncmp(line, control_operators[i], \
			ft_strlen(control_operators[i])) == 0)
		{
			op = ft_strdup(control_operators[i]);
			if (op == NULL)
				function_error("strdup");
			*rest = line + ft_strlen(op);
			token->word = op;
			return (token);
		}
		i++;
	}
	assert_error("Unexpected operator");
	return (NULL);
}
