/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:17:51 by hhurnik           #+#    #+#             */
/*   Updated: 2025/08/20 17:29:17 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall_on_grid(float intersection_x, float intersection_y, t_cub3d *data)
{
	int	map_x_grid;
	int	map_y_grid;

	map_x_grid = (int)(intersection_x / GRID_SIZE);
	map_y_grid = (int)(intersection_y / GRID_SIZE);
	if (map_x_grid < 0 || map_x_grid >= data->map_cols || map_y_grid < 0
		|| map_y_grid >= data->map_rows)
		return (1);
	if (data->map[map_y_grid][map_x_grid] == '1')
		return (1);
	return (0);
}

// calculate the distance to the wall for a specific ray
float	distance_to_the_wall(t_player *player, int column, float intersection_x,
		float intersection_y)
{
	float	distance;
	float	ray_angle;
	float	delta_y;
	float	delta_x;

	delta_y = intersection_y - player->player_y;
	delta_x = intersection_x - player->player_x;
	ray_angle = get_absolute_ray_angle(column, player);
	if (fabsf((float)(ray_angle - (M_PI / 2.0f))) < EPSILON)
		distance = fabsf(delta_y);
	else if (fabsf((float)(ray_angle - (3.0f / 2.0f) * M_PI)) < EPSILON)
		distance = fabsf(delta_y);
	else if (fabsf(ray_angle - 0.0f) < EPSILON)
		distance = fabsf(delta_x);
	else if (fabsf((float)(ray_angle - M_PI)) < EPSILON)
		distance = fabsf(delta_x);
	else if (ray_angle > 0.0f && ray_angle < M_PI / 2.0f)
		distance = fabsf((delta_x) / cosf(ray_angle));
	else if (ray_angle > M_PI / 2.0f && ray_angle < M_PI)
		distance = fabsf((delta_x) / sinf(ray_angle - (M_PI / 2.0f)));
	else if (ray_angle > M_PI && ray_angle < (3.0f / 2.0f) * M_PI)
		distance = fabsf((delta_x) / cosf(ray_angle - M_PI));
	else if (ray_angle > (3.0f / 2.0f) * M_PI && ray_angle < 2.0f * M_PI)
		distance = fabsf((delta_x) / sinf(ray_angle - (3.0f / 2.0f) * M_PI));
	return (distance);
}

/* Finds the first horizontal intersection and if there's no wall,
it calculates the position of the next intersection*/
void	find_horizontal_intersection(t_player *player, t_cub3d *data,
		float ray_angle, t_intersection *intersection)
{
	float	horizontal_step_x;
	float	horizontal_step_y;

	horizontal_step_x = find_horizontal_step_x(ray_angle);
	horizontal_step_y = find_horizontal_step_y(ray_angle);
	intersection->intersection_hor_y
		= find_first_horizontal_intersection_y(player, ray_angle);
	intersection->intersection_hor_x
		= find_first_horizontal_intersection_x(player, ray_angle);
	while (is_wall_on_grid(intersection->intersection_hor_x,
			intersection->intersection_hor_y, data) != 1)
	{
		intersection->intersection_hor_y += horizontal_step_y;
		intersection->intersection_hor_x += horizontal_step_x;
	}
}

/* Finds the first vertical intersection and if there's no wall,
it calculates the position of the next intersection*/
void	find_vertical_intersection(t_player *player, t_cub3d *data,
		float ray_angle, t_intersection *intersection)
{
	float	vertical_step_x;
	float	vertical_step_y;

	vertical_step_x = find_vertical_step_x(ray_angle);
	vertical_step_y = find_vertical_step_y(ray_angle);
	intersection->intersection_ver_y
		= find_first_vertical_intersection_y(player, ray_angle);
	intersection->intersection_ver_x
		= find_first_vertical_intersection_x(player, ray_angle);
	while (is_wall_on_grid(intersection->intersection_ver_x,
			intersection->intersection_ver_y, data) != 1)
	{
		intersection->intersection_ver_y += vertical_step_y;
		intersection->intersection_ver_x += vertical_step_x;
	}
}

void	find_wall(t_player *player, t_cub3d *data, float ray_angle,
		t_intersection *intersection)
{
	find_horizontal_intersection(player, data, ray_angle, intersection);
	find_vertical_intersection(player, data, ray_angle, intersection);
}
