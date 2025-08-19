/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:28:11 by zslowian          #+#    #+#             */
/*   Updated: 2024/03/03 19:28:11 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		if (!*s1)
			return (0);
		s1++;
		s2++;
	}
	return (0);
}

/* static int	ft_check(char one, char two, size_t i, size_t n);

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (ft_check(s1[i], s2[i], i, n))
		i++;
	if (s1[i] == s2[i])
		return (0);
	else
	{
		return (s1[i] - s2[i]);
	}	
}

static int	ft_check(char one, char two, size_t i, size_t n)
{
	int first;
	int second;

	first = ((one == two) && one != '\0');
	second = (two != '\0' && i < n - 1);
	return first && second;
} */
