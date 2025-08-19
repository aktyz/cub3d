/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:25:37 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/19 17:59:52 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//collision check, update player's position
void	ft_update_player_pos(t_cub3d *data, t_int_position map_grid,
			t_float_position new)
{
	if (map_grid.y >= 0 && map_grid.y < data->map_rows &&
		map_grid.x >= 0 && map_grid.x < data->map_cols &&
		data->map[map_grid.y][map_grid.x] != '1')
	{
		data->player.player_x = new.x;
		data->player.player_y = new.y;
	}
}