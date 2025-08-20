/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vertical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:34:29 by hhurnik           #+#    #+#             */
/*   Updated: 2025/08/19 17:34:31 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	find_first_vertical_intersection_x(t_player *player, float ray_angle)
{
	float	first_intersection_x;

	if (is_ray_facing_right(ray_angle) == 0)
		first_intersection_x = floorf(player->player_x / GRID_SIZE) * GRID_SIZE
			- EPSILON;
	else
		first_intersection_x = floorf(player->player_x / GRID_SIZE) * GRID_SIZE
			+ GRID_SIZE;
	return (first_intersection_x);
}

float	find_first_vertical_intersection_y(t_player *player, float ray_angle)
{
	float	first_intersection_y;
	float	first_intersection_x;

	first_intersection_x = find_first_vertical_intersection_x(player,
			ray_angle);
	if (is_ray_vertical(ray_angle))
		return (INFINITY);
	first_intersection_y = player->player_y + (first_intersection_x
			- player->player_x) * tanf(ray_angle);
	return (first_intersection_y);
}

/*find the step for x to move each intersection by 
(in case there's no wall on the current one)*/
float	find_vertical_step_x(float ray_angle)
{
	if (is_ray_facing_right(ray_angle) == 1)
		return (GRID_SIZE);
	else
		return ((-1) * GRID_SIZE);
}

/*find the step for y to move each intersection by 
(in case there's no wall on the current one)*/
float	find_vertical_step_y(float ray_angle)
{
	float	x_step;

	x_step = find_vertical_step_x(ray_angle);
	if (is_ray_vertical(ray_angle))
	{
		if (is_ray_facing_up(ray_angle))
			return (-GRID_SIZE);
		else
			return (GRID_SIZE);
	}
	else
	{
		x_step = find_vertical_step_x(ray_angle);
		return (x_step * tanf(ray_angle));
	}
}
