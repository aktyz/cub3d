/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:40:48 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/12 19:19:37 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_store_rgb(int color_storage[3], char **color_values,
	t_cub3d *data);
bool	are_all_colors(t_cub3d *data);

void	ft_store_rgb(int color_storage[3], char **color_values,
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

bool	are_all_colors(t_cub3d *data)
{
	if (data->colors->ceiling_color[0] == -1 || data->colors->ceiling_color[1] == -1
		|| data->colors->ceiling_color[2] == -1)
		return (false);
	if (data->colors->floor_color[0] == -1 || data->colors->floor_color[1] == -1
		|| data->colors->floor_color[2] == -1)
		return (false);
	return (true);
}

void	init_colors(t_cub3d *data)
{
	data->colors = ft_calloc(1, sizeof(t_colors));
	if (data->colors == NULL)
		ft_error(MEM_ERROR, "init_colors", data);
	data->colors->ceiling_color[0] = -1;
	data->colors->ceiling_color[1] = -1;
	data->colors->ceiling_color[2] = -1;
	data->colors->floor_color[0] = -1;
	data->colors->floor_color[1] = -1;
	data->colors->floor_color[2] = -1;
}
