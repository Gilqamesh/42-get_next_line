/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:46:57 by edavid            #+#    #+#             */
/*   Updated: 2021/06/25 13:52:35 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>
#include <limits.h>

int	get_next_line(int fd, char **line)
{
	char			*tmp_str;
	int				tmp_index;
	static char		*buffers[OPEN_MAX] = {0};
	int				read_result;
	int				cur_buf_len;

	if (!buffers[fd])
	{
		buffers[fd] = malloc(BUFFER_SIZE + 1);
		cur_buf_len = BUFFER_SIZE;
		read_result = read(fd, buffers[fd], BUFFER_SIZE);
		if (read_result == -1)
		{
			free(buffers[fd]);
			buffers[fd] = (char *)0;
			return (-1);
		}
		buffers[fd][read_result] = '\0';
		return (get_next_line(fd, line));
	}
	else
	{
		cur_buf_len = ft_strlen(buffers[fd]);
		tmp_index = contains_newline(buffers[fd], cur_buf_len);
	}
	if (tmp_index == cur_buf_len)
	{
		tmp_str = ft_strdup_v2(buffers[fd], cur_buf_len);
		free(buffers[fd]);
		cur_buf_len += BUFFER_SIZE;
		buffers[fd] = malloc(cur_buf_len + 1);
		read_result = read(fd, buffers[fd], BUFFER_SIZE);
		if (read_result == -1)
		{
			free(tmp_str);
			free(buffers[fd]);
			buffers[fd] = (char *)0;
			return (-1);
		}
		if (!read_result)
		{
			*line = tmp_str;
			free(buffers[fd]);
			buffers[fd] = (char *)0;
			return (0);
		}
		buffers[fd][read_result] = '\0';
		buffers[fd] = ft_strjoin_v3(&tmp_str, &buffers[fd]);
		return (get_next_line(fd, line));
	}
	*line = ft_strdup_v2(buffers[fd], tmp_index);
	ft_memmove(buffers[fd], buffers[fd] + tmp_index + 1, cur_buf_len - tmp_index);
	return (1);
}
