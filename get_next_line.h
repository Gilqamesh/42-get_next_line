/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 15:03:30 by edavid            #+#    #+#             */
/*   Updated: 2021/06/23 14:37:01 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
int		get_next_line(int fd, char **line);
size_t	ft_strlen(const char *s);
void	ft_strlcpy(char *dst, const char *src, size_t size);
int		contains_newline(char *str, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
char 	*ft_strjoin_v2(char **s1, char const *s2);
char	*ft_strdup(const char *s);

#endif
