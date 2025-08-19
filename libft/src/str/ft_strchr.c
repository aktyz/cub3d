/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:09:37 by zslowian          #+#    #+#             */
/*   Updated: 2024/03/03 20:09:37 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	The strchr() function returns a pointer to the first occurrence
	of the character c in the string s.
	The strchr() and strrchr() functions return a pointer to the
	matched character or NULL if the character is not found.  The
	terminating null byte is considered part of the string, so that
	if c is specified as '\0', these functions return a pointer to
	the terminator. */

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s != (char)c)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}

/* char	*ft_strchr(const char *s, int c)
{
	char		*ptr;
	size_t		length;

	ptr = (char *)s;
	length = ft_strlen(s);
	if (c == '\0')
	{
		return (ptr + length);
	}
	else
	{
		while (*ptr != c && *ptr != '\0')
		{
			ptr++;
		}
		if (*ptr == c)
			return (ptr);
		else
			return (0);
	}
}
 */