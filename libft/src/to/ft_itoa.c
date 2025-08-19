/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:28:34 by zslowian          #+#    #+#             */
/*   Updated: 2024/09/26 21:19:08 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates with malloc and returns a string representing the integer
received as an argument. Negative numbers must be handled

return value: The string representing the integer
NULL if allocation fails
*/

static char	*ft_nbr_to_str(int n, int len, int is_negative);
static int	get_num_of_char(int n, int is_negative);

char	*ft_itoa(int n)
{
	int		len;
	int		is_negative;

	if (!n)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	is_negative = 0;
	if (n < 0)
	{
		is_negative = 1;
		n = -n;
	}
	len = get_num_of_char(n, is_negative);
	return (ft_nbr_to_str(n, len, is_negative));
}

static char	*ft_nbr_to_str(int n, int len, int is_negative)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * len);
	if (!ptr)
		return (0);
	ptr[len - 1] = '\0';
	len--;
	while (n > 0 && len > 0)
	{
		ptr[len - 1] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
	if (is_negative && len > 0)
		ptr[0] = '-';
	return (ptr);
}

/*
	get_num_of_char counts the necessary chars
	to put a number into a String
	it counts in the '\0';
*/

static int	get_num_of_char(int n, int is_negative)
{
	int	i;

	i = 1;
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	if (is_negative)
		i++;
	return (i);
}
