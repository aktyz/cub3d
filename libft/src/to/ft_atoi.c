/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:12:08 by zslowian          #+#    #+#             */
/*   Updated: 2025/04/27 16:11:23 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_return_overflow(int is_negative);

/**
 * Converts the initial portion of the string to int representation.
 *
 * If char other than digit encountered, the function stops reading and
 * returns what has been transformed so far.
 *
 * If the result is bigger than 2147483647 it returns 2147483647, if
 * the result is smaller than -2147483648 it returns -2147483648.
 *
*/
int	ft_atoi(const char *str)
{
	int	i;
	int	is_negative;
	int	result;

	i = 0;
	is_negative = 1;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == 43 && str[i + 1] != 45)
		i++;
	if (str[i] == 45)
	{
		is_negative = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (result > 2147483647 / 10 || (result == 2147483647 / 10
				&& str[i] - 48 > 7))
			return (ft_return_overflow(is_negative));
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * is_negative);
}

static int	ft_return_overflow(int is_negative)
{
	if (is_negative == 1)
		return (2147483647);
	else
		return (-2147483648);
}
