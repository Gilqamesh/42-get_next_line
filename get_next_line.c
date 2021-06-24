/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 15:10:42 by edavid            #+#    #+#             */
/*   Updated: 2021/06/24 17:00:57 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <limits.h>

static int	make_empty_string(char **line)
{
	*line = malloc(1);
	if (!*line)
		return (-1);
	**line = '\0';
	return (0);
}

static int	reset_vars(char **buffer, int *has_s, int *bytes_s)
{
	if (buffer)
		free(*buffer);
	if (has_s)
		*has_s = 0;
	if (bytes_s)
		*bytes_s = 0;
	return (-1);
}

int get_next_line(int fd, char **line)
{
	char			*tmp_str; 
	int				tmp_index;
	static char		*buffers[OPEN_MAX] = {0};
	int				read_result;
	int				cur_buf_len;

	int cur_buf_len;
	if (!buffers[fd])
		buffers[fd] = malloc(BUFFER_SIZE + 1);
	cur_buf_len = ft_strlen(buffers[fd]);
	tmp_index = contains_newline(buffers[fd], cur_buf_len);
	if (tmp_index == cur_buf_len)
	{
		tmp_str = buffers[fd];
		buffers[fd] = malloc(cur_buf_len + BUFFER_SIZE + 1);
		read_result = read(fd, buffers[fd] + cur_buf_len, BUFFER_SIZE);
		buffers[fd] = ft_strjoin_v2(&tmp_str, buffers[fd] + cur_buf_len);
		if (!read_result)
		{
			*line = buffers[fd];
			return (0);
		}
		return (get_next_line(fd, line));
	}
	*line = ft_strdup_v2();





	/*
	if (!bytes_stashed)
	{
		buffer_stash = malloc(BUFFER_SIZE);
		bytes_stashed = read(fd, buffer_stash, BUFFER_SIZE);
		if (bytes_stashed < 0)
			return (reset_vars(&buffer_stash, &has_saved_str, &bytes_stashed));
		if (!bytes_stashed)
		{
			free(buffer_stash);
			if (has_saved_str)
			{
				has_saved_str = 0;
				return (0);
			}
			return (make_empty_string(line));
		}
	}
	tmp_index = contains_newline(buffer_stash, bytes_stashed);
	tmp_str = malloc(tmp_index + 1);
	if (!tmp_str)
		return (reset_vars(&buffer_stash, &has_saved_str, &bytes_stashed));
	ft_strlcpy(tmp_str, buffer_stash, tmp_index + 1);
	if (has_saved_str)
		*line = ft_strjoin_v2(line, tmp_str);
	else
		*line = ft_strdup(tmp_str);
	free(tmp_str);
	if (tmp_index == bytes_stashed)
	{
		reset_vars(&buffer_stash, (int *)0, &bytes_stashed);
		has_saved_str = 1;
		return (get_next_line(fd, line));
	}
	has_saved_str = 0;
	bytes_stashed -= tmp_index + 1;
	if (!bytes_stashed)
		free(buffer_stash);
	else
		ft_memmove(buffer_stash, buffer_stash + tmp_index + 1, BUFFER_SIZE);
	return (1);
	*/
}
