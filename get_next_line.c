/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 15:10:42 by edavid            #+#    #+#             */
/*   Updated: 2021/06/22 17:34:52 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

int get_next_line(int fd, char **line)
{
	ssize_t			read_bytes;
	static size_t	bytes_stashed = 0;
	static char 	*buffer_stash = (char *)0;
	char			*tmp_str;
	char			*saved_str;
	int				tmp_index;
	static int		has_saved_str = 0;

	if (!bytes_stashed)
	{
		buffer_stash = malloc(BUFFER_SIZE);
		if (!buffer_stash)
		{
			has_saved_str = 0;
			return (-1);
		}
	}
	read_bytes = read(fd, buffer_stash + bytes_stashed, BUFFER_SIZE - bytes_stashed);
	bytes_stashed += read_bytes;
	if (read_bytes < 0 || (!read_bytes && !has_saved_str))
	{
		has_saved_str = 0;
		bytes_stashed = 0;
		free(buffer_stash);
		if (read_bytes == 0)
		{
			*line = malloc(1);
			**line = '\0';
		}
		return (read_bytes);
	}
	tmp_index = contains_newline(buffer_stash, bytes_stashed);
	if (tmp_index < 0)
		tmp_str = malloc(bytes_stashed + 1);
	else
		tmp_str = malloc(tmp_index + 1);
	if (!tmp_str)
	{
		has_saved_str = 0;
		bytes_stashed = 0;
		free(buffer_stash);
		return (-1);
	}
	if (tmp_index < 0)
		ft_strlcpy(tmp_str, buffer_stash, bytes_stashed + 1);
	else
		ft_strlcpy(tmp_str, buffer_stash, tmp_index + 1);
	if (has_saved_str)
	{
		saved_str = ft_strjoin(*line, tmp_str);
		free(*line);
		*line = saved_str;
	}
	else
		*line = ft_strdup(tmp_str);
	free(tmp_str);
	if (tmp_index < 0)
	{
		free(buffer_stash);
		bytes_stashed = 0;
		if (bytes_stashed == BUFFER_SIZE)
		{
			has_saved_str = 1;
			return (get_next_line(fd, line));
		}
		return (1);
	}
	bytes_stashed -= tmp_index + 1;
	ft_memmove(buffer_stash, buffer_stash + tmp_index + 1, BUFFER_SIZE);
	return (1);
}
