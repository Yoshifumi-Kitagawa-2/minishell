/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_3_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:28:55 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/14 19:32:31 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_input(t_info *info, int i)
{
	char	**tmp;

	tmp = NULL;
	info->input_fd = open(info->argv[i + 1], O_RDONLY);
	if (info->input_fd == -1)
		err_exit(info->argv[i + 1], "command not found");
	dup2(info->input_fd, STDIN);
	remove_redirect(tmp, info, i);
}

void	do_output(t_info *info, int i)
{
	char	**tmp;

	tmp = NULL;
	info->output_fd = open(info->argv[i + 1],
			(O_WRONLY | O_CREAT | O_TRUNC), 0644);
	if (info->output_fd == -1)
		function_error("open");
	if (info->argv[i + 2] == NULL)
		dup2(info->output_fd, STDOUT);
	remove_redirect(tmp, info, i);
}

void	do_heredoc_one(t_info *info, int i)
{
	char	**tmp;

	tmp = NULL;
	info->input_fd = open(".heredoc", O_RDONLY);
	if (info->input_fd == -1)
		function_error("open");
	dup2(info->input_fd, STDIN);
	remove_redirect(tmp, info, i);
}

void	do_heredoc_not_one(t_info *info, int i)
{
	char	**tmp;

	tmp = NULL;
	info->input_fd = open(".heredoc", O_RDONLY);
	if (info->input_fd == -1)
		function_error("open");
	dup2(info->input_fd, STDIN);
	remove_redirect(tmp, info, i);
}

void	do_append(t_info *info, int i)
{
	char	**tmp;

	tmp = NULL;
	info->output_fd = open(info->argv[i + 1],
			(O_WRONLY | O_CREAT | O_APPEND), 0644);
	if (info->output_fd == -1)
		function_error("open");
	if (info->argv[i + 2] == NULL)
		dup2(info->output_fd, STDOUT);
	remove_redirect(tmp, info, i);
}
