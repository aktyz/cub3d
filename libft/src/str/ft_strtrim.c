/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:41:38 by zslowian          #+#    #+#             */
/*   Updated: 2024/03/24 21:20:16 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_trim(char c, char const *set);
static char	*new_str(char const *s1, size_t start, size_t len);

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen((const char *)s1) - 1;
	if (end == -1)
		return (ft_strdup(""));
	while (to_trim(s1[start], set))
		start++;
	while (to_trim(s1[end], set))
		end--;
	return (new_str(s1, start, end - (start - 1)));
}

static int	to_trim(char c, char const *set)
{
	char	*p;

	p = (char *)set;
	while (*p != '\0')
	{
		if (*p == c)
			return (1);
		p++;
	}
	return (0);
}

static char	*new_str(char const *s1, size_t start, size_t len)
{
	char	*str;
	size_t	i;

	if (len <= 0 || start >= ft_strlen((const char *)s1))
		return (ft_strdup(""));
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = s1[start + i];
		i++;
	}
	return (str);
}
