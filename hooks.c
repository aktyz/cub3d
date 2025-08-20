/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:34:27 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/20 11:34:30 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int keycode, t_cub3d *data)
{
	if (keycode == XK_Escape)
		close_game(data);
	if (keycode == XK_Left)
		data->input.turn_left = true;
	else if (keycode == XK_Right)
		data->input.turn_right = true;
	else if (keycode == KEY_D)
		data->input.move_right = true;
	else if (keycode == KEY_A)
		data->input.move_left = true;
	else if (keycode == KEY_W)
		data->input.move_forward = true;
	else if (keycode == KEY_S)
		data->input.move_backward = true;
	return (0);
}

int	handle_keyrelease(int keycode, t_cub3d *data)
{
	if (keycode == XK_Left)
		data->input.turn_left = false;
	else if (keycode == XK_Right)
		data->input.turn_right = false;
	else if (keycode == KEY_D)
		data->input.move_right = false;
	else if (keycode == KEY_A)
		data->input.move_left = false;
	else if (keycode == KEY_W)
		data->input.move_forward = false;
	else if (keycode == KEY_S)
		data->input.move_backward = false;
	return (0);
}

void	look_right(t_cub3d *data)
{
	data->player.player_angle += ROTATION_SPEED;
	if (data->player.player_angle >= 2.0f * M_PI)
		data->player.player_angle -= 2.0f * M_PI;
}

void	look_left(t_cub3d *data)
{
	data->player.player_angle -= ROTATION_SPEED;
	if (data->player.player_angle < 0)
		data->player.player_angle += 2.0f * M_PI;
}
