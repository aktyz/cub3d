/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:24:41 by zslowian          #+#    #+#             */
/*   Updated: 2025/06/17 20:28:40 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_is_alphanumeric(char *token);

/**
 * Function checks if token contains anything else than white spaces.
 * If it contains it - the function returns true and should be added
 * to the token list.
 * Otherwise it contains only whitespace signs and doesn't need to be
 * added.
 *
 */
bool	ft_is_alphanumeric(char *token)
{
	char *ptr;

	ptr = token;
	while (*ptr)
	{
		if (ft_isalnum(*ptr))
			return(true);
		ptr++;
	}
	return (false);
}
