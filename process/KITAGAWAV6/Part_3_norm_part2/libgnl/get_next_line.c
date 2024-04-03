/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:00:31 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/02/27 15:55:36 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../includes/minishell.h"

char	*do_it(char **save, int fd, char *line)
{
	ssize_t	buf_status;
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line[0] = '\0';
	if (save && *save)
		line = ft_strjoin_with_free(line, *save, FIRST_PARAM);
	buf_status = 1;
	while (buf_status > 0 && !ft_strchr(line, '\n'))
	{
		buf_status = read(fd, buf, BUFFER_SIZE);
		if (buf_status < 0)
			get_it_freed(&line);
		else
		{
		buf[buf_status] = '\0';
		line = ft_strjoin_with_free(line, buf, FIRST_PARAM);
		}
	}
	get_it_freed(save);
	get_it_freed(&buf);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*pointer_nl;
	static char	*save[257];

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char) * 1);
	if (!line)
		return (NULL);
	line = do_it(&save[fd], fd, line);
	pointer_nl = NULL;
	if (line)
		pointer_nl = ft_strchr(line, '\n');
	if (pointer_nl)
	{
		save[fd] = ft_strjoin_with_free(pointer_nl + 1, "", NONE);
		*(pointer_nl + 1) = '\0';
	}
	else if (line && line[0] == '\0')
		get_it_freed(&line);
	return (line);
}
