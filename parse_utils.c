/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:40:48 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/12 18:28:45 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_store_rgb(unsigned int color_storage[3], char **color_values,
	t_cub3d *data);

void	ft_store_rgb(unsigned int color_storage[3], char **color_values,
	t_cub3d *data)
{
	int		i;
	int		color;

	i = -1;
	while (++i < 3)
	{
		if (!color_values[i])
			ft_error(COLOR, "ft_store_rgb - too few rgb", data);
		color = ft_atoi((const char *)color_values[i]);
		if (color < 0 || color > 255)
			ft_error(COLOR, "ft_store_rgb - rgb out of range", data);
		color_storage[i] = color;
	}
}
