/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_4_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:16:13 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/31 12:36:38 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_double_quote(char **p, char **new_word, t_environ *list)
{
	*p += 1;
	while (**p != DOUBLE_QUOTE)
	{
		if (**p == '\0')
			assert_error("Unclosed single quote");
		append_char(new_word, **p);
		*p += 1;
	}
	*p += 1;
	while (ft_strchr(*new_word, '$') && g_signal.not_expand_flag == 0)
		*new_word = double_variable_expand(*new_word, list);
}

void	expand_status(char **p, char **new_word)
{
	*p += 1;
	*new_word = ft_itoa(g_signal.status);
}

void	norm_expansion(char **p, char **var)
{
	if (**p == ' ' || **p == '\0')
	{
		*var = x_strdup("\0");
		g_signal.not_expand_flag = 1;
	}
	else if (ft_isdigit(**p))
	{
		while (**p != ' ' && **p != '\0')
		{
			append_char(var, **p);
			g_signal.not_expand_flag = 1;
			*p += 1;
		}
	}
	else if (not_allowed_variant_character(*p))
		check_variable_character(var, p);
	else
		*var = ft_strndup(*p, ft_strchr(*p, '\0') - *p);
}

void	expansion(char **p, char **new_word, t_environ *list)
{
	char	*var;

	var = NULL;
	if (ft_strchr(*p, '$') || ft_strchr(*p, '\"') || ft_strchr(*p, '\''))
	{
		while (!(**p == '$' || **p == '\"' || **p == '\''))
		{
			append_char(&var, **p);
			*p += 1;
		}
	}
	else
		norm_expansion(p, &var);
	if (*new_word == NULL)
		*new_word = create_new_word_if_null(var, list);
	else if (*new_word != NULL)
		create_new_word_if_not_null(new_word, var, list);
	free(var);
}

bool	handle_after_doll(char **p, char **new_word, t_environ *list)
{
	if (**p == '?')
		expand_status(p, new_word);
	else if (**p == DOUBLE_QUOTE && *(*p + 1) == DOUBLE_QUOTE)
		handle_empty_str(p, new_word);
	else if (**p == SINGLE_QUOTE && *(*p + 1) == SINGLE_QUOTE)
		handle_empty_str(p, new_word);
	else if (**p == DOUBLE_QUOTE)
		remove_double_quote(p, new_word, list);
	else if (**p == SINGLE_QUOTE)
		remove_single_quote(p, new_word);
	else
		return (false);
	return (true);
}
