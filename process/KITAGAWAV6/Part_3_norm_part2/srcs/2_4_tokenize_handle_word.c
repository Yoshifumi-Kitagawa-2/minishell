/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_4_tokenize_handle_word.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:51:56 by yokitaga          #+#    #+#             */
/*   Updated: 2023/03/13 19:53:32 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(char *str, size_t n)
{
	char	*new_str;
	size_t	len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	if (len > n)
		len = n;
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		function_error("malloc");
	ft_memcpy(new_str, str, len);
	new_str[len] = '\0';
	return (new_str);
}

bool	check_single_quote(char **line)
{
	(*line)++;
	while (**line && **line != SINGLE_QUOTE)
		(*line)++;
	if (**line == '\0')
	{
		tokenize_error("Unclosed quote", line, *line);
		return (false);
	}
	else
		return (true);
}

bool	check_double_quote(char **line)
{
	(*line)++;
	while (**line && **line != DOUBLE_QUOTE)
		(*line)++;
	if (**line == '\0')
	{
		tokenize_error("Unclosed quote", line, *line);
		return (false);
	}
	else
		return (true);
}

void	get_end(char **line)
{
	while (**line != '\0' && is_metacharacter(**line) == false && \
		is_control_operator(*line) == false)
	{
		if (**line == SINGLE_QUOTE)
		{
			if (check_single_quote(line) == false)
				break ;
			else
				(*line)++;
		}
		else if (**line == DOUBLE_QUOTE)
		{
			if (check_double_quote(line) == false)
				break ;
			else
				(*line)++;
		}
		else
			(*line)++;
	}
}

t_token	*handle_word(char **rest, char *line)
{
	t_token	*token;
	char	*start;
	char	*end;

	token = new_token(TOKEN_WORD);
	start = line;
	get_end(&line);
	end = line;
	token->word = ft_strndup(start, end - start);
	if (token->word == NULL)
		function_error("strndup");
	*rest = line;
	return (token);
}
