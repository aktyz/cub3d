/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:40:48 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/20 18:09:23 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_store_rgb(int color_storage[3], char **color_values,
			t_cub3d *data);
bool	are_all_colors(t_cub3d *data);

void	ft_store_rgb(int color_storage[3], char **color_values, t_cub3d *data)
{
	int	i;
	int	color;

	i = -1;
	while (++i < 3)
	{
		if (!color_values[i])
			ft_error(COLOR, "ft_store_rgb - insufficient RGB color"
				"values provided", data);
		color = ft_atoi((const char *)color_values[i]);
		if (color < 0 || color > 255)
			ft_error(COLOR, "ft_store_rgb"
				"- RGB color values must be between 0 and 255", data);
		color_storage[i] = color;
	}
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
