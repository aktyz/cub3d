/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:39:32 by hhurnik           #+#    #+#             */
/*   Updated: 2025/08/20 18:11:48 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_player_and_map(t_cub3d *data)
{
	data->player.player_x = (data->player.start_col + 0.5) * GRID_SIZE;
	data->player.player_y = (data->player.start_row + 0.5) * GRID_SIZE;
	if (data->player.orientation == 'E')
		data->player.player_angle = 0;
	if (data->player.orientation == 'S')
		data->player.player_angle = M_PI / 2.0;
	if (data->player.orientation == 'W')
		data->player.player_angle = M_PI;
	if (data->player.orientation == 'N')
		data->player.player_angle = 3.0 * M_PI / 2.0;
	data->map[data->player.start_row][data->player.start_col] = '0';
}

int	game_loop(t_cub3d *data)
{
	if (data->input.move_right)
		move_right(data);
	if (data->input.move_left)
		move_left(data);
	if (data->input.move_forward)
		move_forward(data);
	if (data->input.move_backward)
		move_backward(data);
	if (data->input.turn_left)
	{
		look_left(data);
	}
	if (data->input.turn_right)
	{
		look_right(data);
	}
	cast_all_rays(&data->player, data);
	calculate_wall_height(data);
	draw_frame(data);
	render_scaled_frame(data);
	return (0);
}

// it will be changed for textures in the future
void	ft_pixel_put(t_img *image, int x, int y, int color)
{
	char	*pxl;

	pxl = image->pix_ptr + (y * image->line_len + x * (image->bpp / 8));
	*(unsigned int *)pxl = color;
}

/*draws a single vertical slice of a textured wall for a given column
 * It calculates the correct texture coordinates (texture_x, texture_y)
 * for each pixel of the wall slice and draws it to the image buffer
 */
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

void	draw_frame(t_cub3d *data)
{
	int	x;
	int	y;
	int floor_color;
	int ceiling_color;
	
	floor_color = rgb_to_int(data->colors->floor_color[0], data->colors->floor_color[1], data->colors->floor_color[2]);
	ceiling_color = rgb_to_int(data->colors->ceiling_color[0], data->colors->ceiling_color[1], data->colors->ceiling_color[2]);

	x = 0;
	while (x < PP_WIDTH)
	{
		y = 0;
		while (y < data->wall.top[x])
		{
			ft_pixel_put(&data->image, x, y, ceiling_color);
			y++;
		}
		draw_wall_slice(data, x);
		y = data->wall.bottom[x];
		while (y < PP_HEIGHT)
		{
			ft_pixel_put(&data->image, x, y, floor_color);
			y++;
		}
		x++;
	}
}
