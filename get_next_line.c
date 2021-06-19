/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 15:10:42 by edavid            #+#    #+#             */
/*   Updated: 2021/06/19 15:51:05 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	get_next_line(int fd, char **line)
{
	static size_t	remaining_bytes = BUFFER_SIZE:
	read(fd, , 1);
}
