/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bonus.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:46:57 by edavid            #+#    #+#             */
/*   Updated: 2021/06/23 14:47:00 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static int	make_empty_string(char **line)
{
	*line = malloc(1);
	if (!*line)
		return (-1);
	**line = '\0';
	return (0);
}

static int	reset_vars(char **buffer, int *has_s, size_t *bytes_s)
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
	int				read_bytes;
	static size_t	bytes_stashed = 0;
	static char 	*buffer_stash = (char *)0;
	char			*tmp_str; 
	int				tmp_index;
	static int		has_saved_str = 0;

	if (!bytes_stashed)
		buffer_stash = malloc(BUFFER_SIZE);
	read_bytes = read(fd, buffer_stash + bytes_stashed, BUFFER_SIZE - bytes_stashed);
	if (read_bytes < 0)
		return (reset_vars(&buffer_stash, &has_saved_str, &bytes_stashed));
	if (!read_bytes && !bytes_stashed)
	{
		free(buffer_stash);
		if (has_saved_str)
		{
			has_saved_str = 0;
			return (0);
		}
		return (make_empty_string(line));
	}
	bytes_stashed += read_bytes;
	tmp_index = contains_newline(buffer_stash, bytes_stashed);
	if (tmp_index < 0)
		tmp_str = malloc(bytes_stashed + 1);
	else
		tmp_str = malloc(tmp_index + 1);
	if (!tmp_str)
		return (reset_vars(&buffer_stash, &has_saved_str, &bytes_stashed));
	if (tmp_index < 0)
		ft_strlcpy(tmp_str, buffer_stash, bytes_stashed + 1);
	else
		ft_strlcpy(tmp_str, buffer_stash, tmp_index + 1);
	if (has_saved_str)
		*line = ft_strjoin_v2(line, tmp_str);
	else
		*line = ft_strdup(tmp_str);
	free(tmp_str);
	if (tmp_index < 0)
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
}
