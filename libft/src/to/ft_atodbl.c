/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atodbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:25:53 by zslowian          #+#    #+#             */
/*   Updated: 2024/11/18 23:25:53 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_collect_integer(long *integer, char **c, int *err);
static void	ft_collect_fraction(double *fraction, double *pow, char **c,
				int *err);

double	ft_atodbl(char *s)
{
	long	integer;
	double	fraction;
	double	pow;
	int		sign;
	int		err;

	integer = 0;
	fraction = 0.0;
	pow = 1;
	sign = 1;
	err = 0;
	while (ft_isspace(*s))
		s++;
	while (*s == '+' || *s == '-')
		if (*s++ == '-')
			sign = -sign;
	while (*s != '.' && *s && !err)
		ft_collect_integer(&integer, &s, &err);
	if (err)
		return (integer * sign);
	if (*s == '.')
		s++;
	while (*s & !err)
		ft_collect_fraction(&fraction, &pow, &s, &err);
	return ((integer + fraction) * sign);
}

static void	ft_collect_integer(long *integer, char **c, int *err)
{
	if (ft_isdigit(**c))
	{
		*integer = (*integer * 10) + (**c - 48);
		(*c)++;
	}
	else
		*err = 1;
}

static void	ft_collect_fraction(double *fraction, double *pow, char **c,
		int *err)
{
	if (ft_isdigit(**c))
	{
		*pow /= 10;
		*fraction = *fraction + (**c - 48) * (*pow);
		(*c)++;
	}
	else
		*err = 1;
}
