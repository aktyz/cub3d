/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:33:17 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/20 11:35:46 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cub3d *data)
{
	float				dx;
	float				dy;
	t_float_position	new;

	dx = cosf(data->player.player_angle) * MOVE_SPEED;
	dy = sinf(data->player.player_angle) * MOVE_SPEED;
	new.x = data->player.player_x + dx;
	new.y = data->player.player_y + dy;
	ft_update_player_pos(data, new);
}

//moves the player backward by subtracting the forward movement components
void	move_backward(t_cub3d *data)
{
	float				dx;
	float				dy;
	t_float_position	new;

	dx = cosf(data->player.player_angle) * MOVE_SPEED;
	dy = sinf(data->player.player_angle) * MOVE_SPEED;
	new.x = data->player.player_x - dx;
	new.y = data->player.player_y - dy;
	ft_update_player_pos(data, new);
}

//moves the player left
void	move_left(t_cub3d *data)
{
	float				dx;
	float				dy;
	float				move_angle;
	t_float_position	new;

	move_angle = data->player.player_angle - (M_PI / 2.0f);
	dx = cosf(move_angle) * MOVE_SPEED;
	dy = sinf(move_angle) * MOVE_SPEED;
	new.x = data->player.player_x + dx;
	new.y = data->player.player_y + dy;
	ft_update_player_pos(data, new);
}

void	move_right(t_cub3d *data)
{
	float				dx;
	float				dy;
	float				move_angle;
	t_float_position	new;

	move_angle = data->player.player_angle + (M_PI / 2.0f);
	dx = cosf(move_angle) * MOVE_SPEED;
	dy = sinf(move_angle) * MOVE_SPEED;
	new.x = data->player.player_x + dx;
	new.y = data->player.player_y + dy;
	ft_update_player_pos(data, new);
}
