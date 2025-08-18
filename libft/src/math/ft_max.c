/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:38:36 by zslowian          #+#    #+#             */
/*   Updated: 2024/11/05 17:51:58 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Function returning maximum of two numbers.
 * 
*/
int	ft_max(int a, int b)
{
	if (a < b)
		return (b);
	else
		return (a);
}
