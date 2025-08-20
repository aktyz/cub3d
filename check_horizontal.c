/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_horizontal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:30:01 by hhurnik           #+#    #+#             */
/*   Updated: 2025/08/19 17:31:35 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	find_first_horizontal_intersection_y(t_player *player, float ray_angle)
{
	float	intersection_y;

	if (is_ray_facing_up(ray_angle) == 1)
		intersection_y = floorf(player->player_y / GRID_SIZE) * GRID_SIZE
			- EPSILON;
	else
		intersection_y = floorf(player->player_y / GRID_SIZE) * GRID_SIZE
			+ GRID_SIZE;
	return (intersection_y);
}

// A.x - first intersection
// based on closest grid y, get the x-value of the point of the intersection
float	find_first_horizontal_intersection_x(t_player *player, float ray_angle)
{
	float	first_intersection_y;
	float	intersection_x;

	first_intersection_y = find_first_horizontal_intersection_y(player,
			ray_angle);
	if (is_ray_horizontal(ray_angle))
		return (INFINITY);
	intersection_x = player->player_x + (first_intersection_y
			- player->player_y) / tanf(ray_angle);
	return (intersection_x);
}

/*find the step for y to move each intersection by 
(in case there's no wall on the current one) */
float	find_horizontal_step_y(float ray_angle)
{
	if (is_ray_facing_up(ray_angle))
		return (-GRID_SIZE);
	else
		return (GRID_SIZE);
}

/*find the step for x to move each intersection by 
(in case there's no wall on the current one) */
float	find_horizontal_step_x(float ray_angle)
{
	float	y_step;
	float	x_step;

	y_step = find_horizontal_step_y(ray_angle);
	x_step = y_step / tanf(ray_angle);
	return (x_step);
}
