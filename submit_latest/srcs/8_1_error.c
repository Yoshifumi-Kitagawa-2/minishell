/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_1_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:33:36 by yokitaga          #+#    #+#             */
/*   Updated: 2023/03/17 18:51:52 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	function_error(char *function_name)
{
	ft_putstr_fd("function error: ", STDERR_FILENO);
	ft_putendl_fd(function_name, STDERR_FILENO);
	exit(1);
}

void	tokenize_error(char *message, char **rest, char *line)
{
	ft_putstr_fd("minishell: syntax error near ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	while (*line)
		line++;
	*rest = line;
	g_signal.status = 258;
	g_signal.other_code = TRUE;
}

void	tokenize_error_2(char *message, char *word)
{
	ft_putstr_fd("minishell: syntax error near ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd(" `", STDERR_FILENO);
	ft_putstr_fd(word, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	g_signal.status = 258;
	g_signal.other_code = TRUE;
}

void	export_not_valid_identifier(char *argv)
{
	my_dprintf(STDERR_FILENO,
		"minishell: export: `%s': not a valid identifier\n", argv);
	g_signal.status = 1;
	g_signal.other_code = TRUE;
}

void	unset_not_valid_identifier(char *argv)
{
	my_dprintf(STDERR_FILENO,
		"minishell: unset: `%s': not a valid identifier\n", argv);
	g_signal.status = 1;
	g_signal.other_code = TRUE;
}
