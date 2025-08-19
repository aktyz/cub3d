/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:19:38 by zslowian          #+#    #+#             */
/*   Updated: 2024/03/07 21:19:38 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	The memchr() function scans the initial n bytes of the memory
	area pointed to by s for the first instance of c.  Both c and the
	bytes of the memory area pointed to by s are interpreted as
	unsigned char.

	The memchr() and memrchr() functions return a pointer to the
	matching byte or NULL if the character does not occur in the
	given memory area. */

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned int	is_char;

	ptr = (unsigned char *) s;
	is_char = (unsigned char) c;
	while (n > 0)
	{
		if (*ptr == is_char)
			return ((void *) ptr);
		ptr++;
		n--;
	}
	return (0);
}
