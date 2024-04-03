/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_1_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:33:20 by yokitaga          #+#    #+#             */
/*   Updated: 2023/04/05 11:35:03 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**expand(t_token *tok, t_environ *list)
{
	char	**array;
	int		heredoc_count;
	int		i;
	int		heredoc_flag;

	i = 0;
	quote_removal(tok, list);
	array = token_list_to_array(tok);
	heredoc_count = count_heredoc(array);
	heredoc_flag = 0;
	while (array[i])
	{
		if (ft_strcmp(array[i], "<<") == 0 && heredoc_flag == 0)
		{
			if (g_signal.expand_in_heredoc == TRUE)
				g_signal.not_expand_flag = 0;
			if (heredoc_count == 1)
				write_to_heredoc_one(array, i, list);
			else
				write_to_heredoc_not_one(array, i, &heredoc_flag, list);
		}
		i++;
	}
	return (array);
}

void	just_append(t_token *tok, char **p, char **new_word)
{
	if (ft_strcmp(tok->word, "<<") == 0 && ft_strchr(tok->next->word, '\"')
		&& ft_strcmp(tok->next->next->word, "<<") == 1)
		g_signal.not_expand_flag = 1;
	if (ft_strcmp(tok->word, "<<") == 0 && ft_strchr(tok->next->word, '\'')
		&& ft_strcmp(tok->next->next->word, "<<") == 1)
		g_signal.not_expand_flag = 1;
	append_char(new_word, **p);
	*p += 1;
}

void	expand_variable(char **p, char **new_word, t_environ *list)
{
	g_signal.do_split = 1;
	*p += 1;
	if (handle_after_doll(p, new_word, list) == false)
		expansion(p, new_word, list);
	if (not_allowed_variant_character(*p))
	{
		while (is_variable_character(**p))
			*p += 1;
	}
	else if (ft_strchr(*p, '$'))
		*p = ft_strchr(*p, '$');
	else
		*p = ft_strchr(*p, '\0');
}

void	remove_single_quote(char **p, char **new_word)
{
	*p += 1;
	while (**p != SINGLE_QUOTE)
	{
		if (**p == '<' || **p == '>')
			g_signal.not_parse_flag = 1;
		if (**p == '\0')
			assert_error("Unclosed single quote");
		if (**p == '$')
			g_signal.not_expand_flag = 1;
		append_char(new_word, **p);
		*p += 1;
	}
	*p += 1;
}
