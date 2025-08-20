/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:39:32 by hhurnik           #+#    #+#             */
/*   Updated: 2025/08/20 18:25:49 by hhurnik          ###   ########.fr       */
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
