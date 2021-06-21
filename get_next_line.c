/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 15:10:42 by edavid            #+#    #+#             */
/*   Updated: 2021/06/21 15:24:27 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#define PRINT_ERR(s) (printf("%s at line: %d\n", s, __LINE__))	// only for debugging, get rid of print and stdio later

int get_next_line(int fd, char **line)
{
	ssize_t			read_bytes;
	static size_t	bytes_stashed = 0;
	static char 	*buffer_stash = (char *)0;
	char			*tmp_str;
	int				tmp_index;
	static int		has_saved_str = 0;

	if (!bytes_stashed) // we do not have a buffer stashed currently
	{
		buffer_stash = malloc(BUFFER_SIZE);
		if (!buffer_stash)
		{
			PRINT_ERR("malloc fail");
			if (has_saved_str)
			{
				free(*line);
				has_saved_str = 0;
			}
			return (-1);
		}
		read_bytes = read(fd, buffer_stash, BUFFER_SIZE);
		bytes_stashed = read_bytes;
		if (read_bytes <= 0) 			// error or first byte is EOF
		{
			/* free stuff before returning here */
			if (read_bytes < 0)
				PRINT_ERR("read fail");
			bytes_stashed = 0;
			free(buffer_stash);
			if (has_saved_str)
			{
				has_saved_str = 0;
				return (1);
			}
			return (read_bytes);
		}
		tmp_index = contains_newline(buffer_stash, read_bytes);
		/* check for newline 		*/
		if (tmp_index >= 0) // contains newline
		{
			// contains newline and its not the first byte
			/* store up to newline excluded in *line, decrement bytes_stashed, offset buffer_stash and return success */
			if (tmp_index < 0)
				tmp_index = read_bytes; // make sure this is working properly and get of the next if as its redundant
			tmp_str = malloc(tmp_index + 1);
			if (!tmp_str)
			{
				PRINT_ERR("malloc fail");
				bytes_stashed = 0;
				free(buffer_stash);
				if (has_saved_str)
				{
					free(*line);
					has_saved_str = 0;
				}
				return (-1);
			}
			ft_strlcpy(tmp_str, buffer_stash, tmp_index + 1);
			if (has_saved_str)
				*line = ft_strjoin(*line, tmp_str);
			else
				*line = tmp_str;
			bytes_stashed -= tmp_index + 1;
			ft_memmove(buffer_stash, buffer_stash + tmp_index + 1, tmp_index + 1);
			return (1);
		}
		if (read_bytes < BUFFER_SIZE) 	// we have read some bytes but encountered EOF without meeting a newline
		{
			/* store the read in line 	*/
			tmp_str = malloc(read_bytes + 1);
			if (!tmp_str)
			{
				PRINT_ERR("malloc fail");
				bytes_stashed = 0;
				/* free stuff before returning with error */
				free(buffer_stash);
				if (has_saved_str)
				{
					free(*line);
					has_saved_str = 0;
				}
				return (-1);
			}
			ft_strlcpy(tmp_str, buffer_stash, read_bytes + 1);
			if (has_saved_str)
				*line = ft_strjoin(*line, tmp_str);
			else
				*line = tmp_str;
			/* free the buffer_stash	*/
			free(buffer_stash);
			bytes_stashed = 0;
			/* return success			*/
			return (1);
		}
		// ! LOOKS CORRECT UNTIL HERE !
		// we do not have a newline and have read in BUFFER_SIZE amount
		/* saved_str = strjoin(saved_str, buffer_stash), free buffer_stash and reset bytes_stashed, call get_next_line again */
		*line = malloc(BUFFER_SIZE + 1);
		if (!*line)
		{
			PRINT_ERR("malloc fail");
			bytes_stashed = 0;
			free(buffer_stash);
			return (-1);
		}
		ft_strlcpy(*line, buffer_stash, BUFFER_SIZE + 1);
		bytes_stashed = 0;
		free(buffer_stash);
		return (1);
	}
	else 				// we have a stash which we have to deal with first
	{
		/* copy remaining bytes and then read again */
		tmp_str = malloc(bytes_stashed + 1);
		if (!tmp_str)
		{
			PRINT_ERR("malloc fail");
			bytes_stashed = 0;
			free(buffer_stash);
			return (-1);
		}
		ft_strlcpy(tmp_str, buffer_stash, bytes_stashed + 1);
		/* read BUFFER_SIZE - bytes_stashed		*/
		read_bytes = read(fd, buffer_stash, BUFFER_SIZE - bytes_stashed);
		if (read_bytes < 0) // error
		{
			/* free everything and return with error */
			PRINT_ERR("read fail");
			bytes_stashed = 0;
			free(buffer_stash);
			free(tmp_str);
			return (-1);
		}
		if (!read_bytes) // first byte is EOF
		{
			/* find out if we have a new line stored and handle it accordingly */
			tmp_index = contains_newline(tmp_str, bytes_stashed);
			if (tmp_index >= 0) // stored line contains newline
			{
				/* store newline in *line 			*/
				*line = malloc(tmp_index + 1);
				if (!*line)
				{
					PRINT_ERR("malloc fail");
					bytes_stashed = 0;
					free(buffer_stash);
					return (-1);
				}
				ft_strlcpy(*line, tmp_str, tmp_index + 1);
				/* store remaining in buffer_stash 	*/
				ft_strlcpy(buffer_stash, tmp_str + tmp_index + 1, bytes_stashed - tmp_index); // "bytes_stashed - tmp_index" this part is probably wrong, needs further analysis
				/* free *tmp						*/
				free(tmp_str);
				/* reset bytes_stashed				*/
				bytes_stashed = 0;
				/* return success					*/
				return (1);
			}
			// stored line does not contain newline
			/* store it in *line and return EOF */
			*line = malloc(bytes_stashed + 1);
			if (!*line)
			{
				PRINT_ERR("malloc fail");
				bytes_stashed = 0;
				free(buffer_stash);
				return (-1);
			}
			ft_strlcpy(*line, tmp_str, bytes_stashed + 1);
			free(tmp_str);
			free(buffer_stash);
			return (0);
		}
		// we have bytes in tmp and in buffer_stash
		/* merge tmp into buffer_stash */
		ft_strlcpy(buffer_stash + read_bytes, tmp_str, bytes_stashed + 1);	// not sure about the "bytes_stashed + 1"
		free(tmp_str);
		/* find out if we have a new line stored and handle it accordingly */
		tmp_index = contains_newline(buffer_stash, BUFFER_SIZE);
		if (tmp_index >= 0)	// buffer_stash contains newline
		{
			*line = malloc(tmp_index + 1);
			if (!*line)
			{
				PRINT_ERR("malloc fail");
				bytes_stashed = 0;
				free(buffer_stash);
				return (-1);
			}
			ft_strlcpy(*line, buffer_stash, tmp_index + 1);
			/* offset buffer_stash to 0, ft_strlcpy will not work because the memory overlaps */
			ft_memmove(buffer_stash, buffer_stash + tmp_index + 1, BUFFER_SIZE - (tmp_index + 1));
			return (1);
		}
		// buffer_stash does not contain newline and EOF has not been reached
		/* store *line 			*/
		*line = malloc(BUFFER_SIZE + 1);
		if (!*line)
		{
			PRINT_ERR("malloc fail");
			bytes_stashed = 0;
			free(buffer_stash);
			return (-1);
		}
		ft_strlcpy(*line, buffer_stash, BUFFER_SIZE + 1);
		/* free and reset stash */
		free(buffer_stash);
		bytes_stashed = 0;
		/* return success 		*/
		return (1);
	}
}
