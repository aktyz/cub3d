/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:43:10 by zslowian          #+#    #+#             */
/*   Updated: 2024/03/24 21:43:10 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Allocates (with malloc(3)) and returns a new string, which is the result
	of the concatenation of ’s1’ and ’s2’. */
char	*ft_strjoin(char const *s1, char const *s2)
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
	return (ptr);
}
