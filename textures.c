/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean — kopia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:18:52 by hhurnik          #+#    #+#             */
/*   Updated: 2025/08/07 23:18:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//get a pixel's color from a texture image
unsigned int get_texture_pixel_color(t_texture_data *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x0); //return black if out of bounds
	pixel = texture->img.pix_ptr + (y * texture->img.line_len + x * (texture->img.bpp / 8));
	return (*(unsigned int *)pixel);
}

//load one texture
void load_single_texture(t_cub3d *data, t_texture_data *tex_data, char *path)
{
	tex_data->img.img_ptr = mlx_xpm_file_to_image(data->mlx, path,
			&tex_data->width, &tex_data->height);
	if (!tex_data->img.img_ptr)
		ft_error(MEM_ERROR, "Failed to load texture", data);
	
	tex_data->img.pix_ptr = mlx_get_data_addr(tex_data->img.img_ptr,
			&tex_data->img.bpp, &tex_data->img.line_len, &tex_data->img.endian);
	if (!tex_data->img.pix_ptr)
		ft_error(MEM_ERROR, "Failed to get texture data addr", data);
}

//main function to load all textures
void load_textures(t_cub3d *data)
{
	load_single_texture(data, &data->textures_data[NO], data->textures->no_texture);
	load_single_texture(data, &data->textures_data[SO], data->textures->so_texture);
	load_single_texture(data, &data->textures_data[WE], data->textures->we_texture);
	load_single_texture(data, &data->textures_data[EA], data->textures->ea_texture);
}