/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:10:02 by zslowian          #+#    #+#             */
/*   Updated: 2024/03/24 21:20:52 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Allocates (with malloc(3)) and returns a substring from the string s
	The substring begins at index 'start' and is of maxiumum size 'len'

	My assumptions: I want this function to be safe - the returned substring
	will be ended by '\0'.

*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (ft_strlen((const char *)s) < start)
	{
		ptr = (char *)malloc(1);
		if (!ptr)
			return (0);
		ptr[0] = '\0';
		return (ptr);
	}
	if (len > ft_strlen((const char *)s) - start)
		len = ft_strlen((const char *)s) - start;
	ptr = (char *) malloc(len + 1);
	if (!ptr && len != 0)
		return (0);
	while (i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*ptr;
// 	char	*substring;
// 	size_t	i;

// 	ptr = (char *)&s[start];
// 	substring = (char *)malloc((len + 1) * sizeof(char));
// 	if (start > ft_strlen((const char *)s) + 1 || !ptr)
// 		return (0);
// 	i = 0;
// 	while (*ptr != '\0' && i < len)
// 	{
// 		substring[i] = *ptr;
// 		ptr++;
// 		i++;
// 	}
// 	substring[i] = '\0';
// 	return (substring);
// }
