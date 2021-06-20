#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	if (size)
	{
		while (--size && *src)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (ft_strlen(src));
}

int		contains_newline(char *str, size_t n)
{
	int	index_of_newline;

	index_of_newline = 0;
	while (n-- && str[index_of_newline])	// probably do not need to check for null
		if (str[index_of_newline] =='\n')
			return (index_of_newline);
	return (-1);
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
