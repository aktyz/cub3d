/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:18:52 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/20 17:58:15 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_clean(t_cub3d *data);
static void	ft_tokens_info_clean(t_cub3d *data);
static void	ft_minilibx_clean(t_cub3d *data);

/**
 * Function used just before exiting the program, it assures no leaks
 * exits in our cub3d.
 *
 */
void	ft_clean(t_cub3d *data)
{
	if (!data)
		return ;
	if (data->infile_fd >= 0)
		close(data->infile_fd);
	ft_tokens_info_clean(data);
	if (data->map)
	{
		ft_clear_char_array(&data->map, data->map_rows);
		data->map = NULL;
	}
	ft_minilibx_clean(data);
	free(data);
}

static void	ft_tokens_info_clean(t_cub3d *data)
{
	if (data->tokens)
	{
		ft_lstclear(&data->tokens, ft_delete_token);
		data->tokens = NULL;
	}
	if (data->textures)
	{
		free(data->textures->no_texture);
		free(data->textures->so_texture);
		free(data->textures->we_texture);
		free(data->textures->ea_texture);
		free(data->textures);
		data->textures = NULL;
	}
	if (data->colors)
	{
		free(data->colors);
		data->colors = NULL;
	}
}

static void	ft_minilibx_clean(t_cub3d *data)
{
	if (data->image.img_ptr)
		mlx_destroy_image(data->mlx, data->image.img_ptr);
	if (data->textures_data[NO].img.img_ptr)
		mlx_destroy_image(data->mlx, data->textures_data[NO].img.img_ptr);
	if (data->textures_data[SO].img.img_ptr)
		mlx_destroy_image(data->mlx, data->textures_data[SO].img.img_ptr);
	if (data->textures_data[WE].img.img_ptr)
		mlx_destroy_image(data->mlx, data->textures_data[WE].img.img_ptr);
	if (data->textures_data[EA].img.img_ptr)
		mlx_destroy_image(data->mlx, data->textures_data[EA].img.img_ptr);
	if (data->mlx)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
}
