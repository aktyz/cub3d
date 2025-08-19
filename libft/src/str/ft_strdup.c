/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:35:52 by zslowian          #+#    #+#             */
/*   Updated: 2024/03/05 08:35:52 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	The strdup() function returns a pointer to a new string which is
	a duplicate of the string s.  Memory for the new string is
	obtained with malloc(3), and can be freed with free(3).

	On success, the strdup() function returns a pointer to the
	duplicated string.  It returns NULL if insufficient memory was
	available, with errno set to indicate the error. */

char	*ft_strdup(char *src)
{
	char	*ptr;
	size_t	check;
	size_t	length;
	size_t	necessary_memory;

	length = ft_strlen((const char *)src);
	necessary_memory = sizeof(char) * (length + 1);
	ptr = (char *)malloc(necessary_memory);
	if (!ptr)
		return (0);
	else
	{
		check = ft_strlcpy(ptr, src, necessary_memory);
		if (check != length)
			return (0);
		return (ptr);
	}
}
