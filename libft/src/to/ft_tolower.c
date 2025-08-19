/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:58:02 by zslowian          #+#    #+#             */
/*   Updated: 2024/03/03 19:58:02 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	If c is an uppercase letter, tolower() returns its lowercase
	equivalent, if a lowercase representation exists in the current
	locale.  Otherwise, it returns c. */

int	ft_tolower(int c)
{
	if (c > 64 && c < 91)
		return (c + 32);
	else
		return (c);
}
