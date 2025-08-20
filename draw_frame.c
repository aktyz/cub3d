/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:23:57 by hhurnik           #+#    #+#             */
/*   Updated: 2025/08/20 18:35:59 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put(t_img *image, int x, int y, int color)
{
	char	*pxl;

	pxl = image->pix_ptr + (y * image->line_len + x * (image->bpp / 8));
	*(unsigned int *)pxl = color;
}

/*draws a single vertical slice of a textured wall for a given column,
 calculates the correct texture coordinates (texture_x, texture_y)
 for each pixel of the wall slice and draws it to the image buffer*/
static void	draw_wall_slice(t_cub3d *data, int x)
{
	t_texture_data	*texture;
	int				y;
	int				texture_x;
	int				texture_y;
	int				dist_from_top;

	texture = &data->textures_data[data->wall.wall_face[x]];
	texture_x = (int)((fmod(data->wall.wall_hit[x], GRID_SIZE) / GRID_SIZE)
			* texture->width);
	if (data->wall.wall_face[x] == SO || data->wall.wall_face[x] == WE)
		texture_x = texture->width - 1 - texture_x;
	y = data->wall.top[x];
	while (y < data->wall.bottom[x])
	{
		dist_from_top = y + (data->wall.wall_height[x] / 2) - (PP_HEIGHT / 2);
		texture_y = (int)(((double)dist_from_top / data->wall.wall_height[x])
				* texture->height);
		ft_pixel_put(&data->image, x, y, get_texture_pixel_color(texture,
				texture_x, texture_y));
		y++;
	}
}

//convert rgb values to a single integer
static int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

/*Draws a full vertical slice of the screen at a given x
** This includes the ceiling, the wall texture, and the floor.
*/
static void	draw_column(t_cub3d *data, int x, int ceil_col, int floor_col)
{
	int	y;

	y = 0;
	while (y < data->wall.top[x])
	{
		ft_pixel_put(&data->image, x, y, ceil_col);
		y++;
	}
	draw_wall_slice(data, x);
	y = data->wall.bottom[x];
	while (y < PP_HEIGHT)
	{
		ft_pixel_put(&data->image, x, y, floor_col);
		y++;
	}
}

/*Renders the entire scene by iterating through every column x,
draws the ceiling, wall and floor for that column*/
void	draw_frame(t_cub3d *data)
{
	int	x;
	int	floor_color;
	int	ceiling_color;

	floor_color = rgb_to_int(data->colors->floor_color[0],
			data->colors->floor_color[1], data->colors->floor_color[2]);
	ceiling_color = rgb_to_int(data->colors->ceiling_color[0],
			data->colors->ceiling_color[1], data->colors->ceiling_color[2]);
	x = 0;
	while (x < PP_WIDTH)
	{
		draw_column(data, x, ceiling_color, floor_color);
		x++;
	}
}
