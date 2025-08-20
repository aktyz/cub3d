/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:40:48 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/20 23:16:11 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_store_rgb(int color_storage[3], char **color_values);
bool	are_all_colors(t_cub3d *data);

bool	ft_store_rgb(int color_storage[3], char **color_values)
{
	int	i;
	int	color;

	i = -1;
	while (++i < 3)
	{
		if (!color_values[i])
			return (true);
		color = ft_atoi((const char *)color_values[i]);
		if (color < 0 || color > 255)
			return (true);
		color_storage[i] = color;
	}
	return (false);
}

bool	are_all_colors(t_cub3d *data)
{
	if (data->colors->ceiling_color[0] == COLOR_INIT_VALUE
		|| data->colors->ceiling_color[1] == COLOR_INIT_VALUE
		|| data->colors->ceiling_color[2] == COLOR_INIT_VALUE)
		return (false);
	if (data->colors->floor_color[0] == COLOR_INIT_VALUE
		|| data->colors->floor_color[1] == COLOR_INIT_VALUE
		|| data->colors->floor_color[2] == COLOR_INIT_VALUE)
		return (false);
	return (true);
}

void	init_colors(t_cub3d *data)
{
	data->colors = ft_calloc(1, sizeof(t_colors));
	if (data->colors == NULL)
		ft_error(MEM_ERROR, "init_colors", data);
	data->colors->ceiling_color[0] = COLOR_INIT_VALUE;
	data->colors->ceiling_color[1] = COLOR_INIT_VALUE;
	data->colors->ceiling_color[2] = COLOR_INIT_VALUE;
	data->colors->floor_color[0] = COLOR_INIT_VALUE;
	data->colors->floor_color[1] = COLOR_INIT_VALUE;
	data->colors->floor_color[2] = COLOR_INIT_VALUE;
}
