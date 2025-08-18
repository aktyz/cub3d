/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:48:43 by zslowian          #+#    #+#             */
/*   Updated: 2024/12/08 00:10:19 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Function takes two strings, join them together and free the memory of the 
 * first string effectively replaced by the result of joining.
 * 
 * Returning the resulting joined string.
 * 
 */
char	*ft_strreplace(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*ptr;

	if (!s2)
		len_s2 = 0;
	else
		len_s2 = ft_strlen(s2);
	if (!s1)
		len_s1 = 0;
	else
		len_s1 = ft_strlen(s1);
	ptr = ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1, len_s1);
	ft_strlcpy(ptr + len_s1, s2, len_s2);
	if (s1)
		free(s1);
	return (ptr);
}
