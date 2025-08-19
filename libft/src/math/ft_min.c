/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:54:30 by zslowian          #+#    #+#             */
/*   Updated: 2024/10/14 21:55:45 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Function returning minimum of two numbers.
 * 
*/
int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
