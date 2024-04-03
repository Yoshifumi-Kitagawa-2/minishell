/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_2_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:45:33 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/14 19:45:47 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_signal_handler(int signal)
{
	(void)signal;
	g_signal.status = 1;
	g_signal.other_code = TRUE;
	close(0);
	write(1, "\n", 1);
}

int	heredoc_signal(void)
{
	signal(SIGINT, &heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
