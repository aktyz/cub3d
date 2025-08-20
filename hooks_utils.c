/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:25:37 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/20 11:32:48 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//collision check, update player's position
void	ft_update_player_pos(t_cub3d *data, t_float_position new)
{
	float	player_radius;
	int		check_points[4][2];
	int		i;

	player_radius = GRID_SIZE * 0.15f;
	check_points[0][0] = (int)((new.x - player_radius) / GRID_SIZE);
	check_points[0][1] = (int)((new.y - player_radius) / GRID_SIZE);
	check_points[1][0] = (int)((new.x + player_radius) / GRID_SIZE);
	check_points[1][1] = (int)((new.y - player_radius) / GRID_SIZE);
	check_points[2][0] = (int)((new.x - player_radius) / GRID_SIZE);
	check_points[2][1] = (int)((new.y + player_radius) / GRID_SIZE);
	check_points[3][0] = (int)((new.x + player_radius) / GRID_SIZE);
	check_points[3][1] = (int)((new.y + player_radius) / GRID_SIZE);
	i = -1;
	while (++i < 4)
	{
		if (check_points[i][1] < 0 || check_points[i][1] >= data->map_rows ||
			check_points[i][0] < 0 || check_points[i][0] >= data->map_cols ||
			data->map[check_points[i][1]][check_points[i][0]] == '1')
			return ;
	}
	data->player.player_x = new.x;
	data->player.player_y = new.y;
}

int	close_game(t_cub3d *data)
{
	ft_clean(data);
	exit(EXIT_SUCCESS);
	return (0);
}
