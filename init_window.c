/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:45:36 by hhurnik           #+#    #+#             */
/*   Updated: 2025/08/20 17:37:03 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_cub3d *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_error(MEM_ERROR, "init_mlx", data);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data->win)
		ft_error(MEM_ERROR, "init_mlx", data);
	data->image.img_ptr = mlx_new_image(data->mlx, PP_WIDTH, PP_HEIGHT);
	if (!data->image.img_ptr)
	{
		ft_error(MEM_ERROR, "init_mlx", data);
	}
	data->image.pix_ptr = mlx_get_data_addr(data->image.img_ptr,
			&data->image.bpp, &data->image.line_len, &data->image.endian);
}

// get pixel color from the smaller image
unsigned int	get_pixel_color(t_img *image, int x, int y)
{
	char	*pixel_address;

	pixel_address = image->pix_ptr + (y * image->line_len + x * (image->bpp
				/ 8));
	return (*(unsigned int *)pixel_address);
}

/*draws a single square of pixels on the screen (one scaled up pixel from the 
source image. Start_x and start_y are the top-left coordinates of the square
*/
void	draw_pixel_square(t_cub3d *data, int start_x, int start_y, int color)
{
	int	x;
	int	y;

	y = start_y;
	while (y < start_y + SCALE)
	{
		x = start_x;
		while (x < start_x + SCALE)
		{
			mlx_pixel_put(data->mlx, data->win, x, y, color);
			x++;
		}
		y++;
	}
}

/*Renders the entire game image (from data->image) to the window
It scales it up by SCALE, iterates through each pixel of the
source image and draws the corresponding scaled square*/
void	render_scaled_frame(t_cub3d *data)
{
	int	src_x;
	int	src_y;
	int	color;

	src_y = 0;
	while (src_y < PP_HEIGHT)
	{
		src_x = 0;
		while (src_x < PP_WIDTH)
		{
			color = get_pixel_color(&data->image, src_x, src_y);
			draw_pixel_square(data, src_x * SCALE, src_y * SCALE, color);
			src_x++;
		}
		src_y++;
	}
}
