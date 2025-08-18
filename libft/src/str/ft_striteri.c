/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:01:44 by zslowian          #+#    #+#             */
/*   Updated: 2024/03/24 21:18:19 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Applies the function 'f' on each character of the string passed as
	argument, passing its index as frist argument.
	Each character is passed by address to 'f' to be modified if necessary

	s: the string on which to iterate
	f: the function to apply on each character
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen((const char *)s);
	while (i < len)
	{
		(*f)(i, &s[i]);
		i++;
	}
}
