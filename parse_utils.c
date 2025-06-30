/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:40:48 by zslowian          #+#    #+#             */
/*   Updated: 2025/06/30 19:00:36 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_store_rgb(unsigned int color_storage[3], char **color_values);

void	ft_store_rgb(unsigned int color_storage[3], char **color_values)
{
	int		i;

	i = -1;
	while (++i < 3)
		color_storage[i] = ft_atoi((const char *)color_values[i]);
}