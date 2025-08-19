/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:59:35 by zslowian          #+#    #+#             */
/*   Updated: 2024/03/04 17:59:35 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	The strrchr() function returns a pointer to the last occurrence of the
	character c in the string s.
	The strchr() and strrchr() functions return a pointer to the
	matched character or NULL if the character is not found.  The
	terminating null byte is considered part of the string, so that
	if c is specified as '\0', these functions return a pointer to
	the terminator. */

char	*ft_strrchr(const char *s, int c)
{
	char		*ptr;

	ptr = NULL;
	while (*s)
	{
		if (*s == (char)c)
			ptr = (char *)s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (ptr);
}
/* char	*ft_strrchr(const char *s, int c)
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
		ptr = ptr + length;
		while (*ptr != c && ptr != s)
		{
			ptr--;
		}
		if (*ptr == c)
			return (ptr);
		else
			return (0);
	}
} */
