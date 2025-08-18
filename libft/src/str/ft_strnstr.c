/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:29:50 by zslowian          #+#    #+#             */
/*   Updated: 2024/03/04 20:29:50 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	The strnstr() function locates the first occurrence of the null-termi-
	nated  string little in the string big, where not more than len charac-
	ters are searched.  Characters that appear after a '\0'	character
	are not searched.

	size_t is return type from sizeof operator and represents
	the size of objects in bytes */

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*little)
		return ((char *) big);
	while (big[i] && i < len)
	{
		while (big[i + j] == little[j] && i + j < len)
		{
			if (!little[j + 1])
				return ((char *)big + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
