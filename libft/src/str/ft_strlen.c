/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:26:01 by zslowian          #+#    #+#             */
/*   Updated: 2024/03/03 19:26:01 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Return length of string str
 *
 */
size_t	ft_strlen(const char *str)
{
	if (str == NULL || !*str)
		return (0);
	return (ft_strlen(str + 1) + 1);
}
