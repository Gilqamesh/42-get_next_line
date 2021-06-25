/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:38:23 by edavid            #+#    #+#             */
/*   Updated: 2021/06/25 13:41:12 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

void	ft_strlcpy(char *dst, const char *src, size_t size)
{
	if (size)
	{
		while (--size && *src)
			*dst++ = *src++;
		*dst = '\0';
	}
}

int		contains_newline(char *str, size_t n)
{
	size_t	index_of_newline;

	index_of_newline = 0;
	while (index_of_newline < n)
	{
		if (str[index_of_newline] == '\n')
			return ((int)index_of_newline);
		index_of_newline++;
	}
	return (index_of_newline);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*r;

	r = dest;
	while (n--)
	{
		if (src > dest)
			*(unsigned char *)dest++ = *(unsigned char *)src++;
		else
			*((unsigned char *)dest + n) = *((unsigned char *)src + n);
	}
	return (r);
}

char 	*ft_strjoin_v3(char **s1, char **s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new;

	s1_len = ft_strlen(*s1);
	s2_len = ft_strlen(*s2);
	new = (char *)malloc(s1_len + s2_len + 1);
	if (!new)
		return ((char *)0);
	ft_strlcpy(new, *s1, s1_len + 1);
	ft_strlcpy(new + s1_len, *s2, s2_len + 1);
	free(*s1);
	free(*s2);
	return (new);
}

char	*ft_strdup_v2(const char *s, int n)
{
	char	*new;

	new = (char *)malloc(n + 1);
	if (!new)
		return ((char *)0);
	ft_strlcpy(new, s, n + 1);
	return (new);
}
