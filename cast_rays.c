/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:06:59 by hhurnik           #+#    #+#             */
/*   Updated: 2025/08/19 18:54:58 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	find_and_set_wall_data(t_cub3d *data, int column, float ray_angle,
		t_intersection *intersection)
{
	float	distance_hor;
	float	distance_ver;

	distance_hor = distance_to_the_wall(&data->player, column,
			intersection->intersection_hor_x, intersection->intersection_hor_y);
	distance_ver = distance_to_the_wall(&data->player, column,
			intersection->intersection_ver_x, intersection->intersection_ver_y);
	if (distance_hor <= distance_ver)
	{
		data->wall.wall_hit[column] = intersection->intersection_hor_x;
		if (is_ray_facing_up(ray_angle))
			data->wall.wall_face[column] = SO;
		else
			data->wall.wall_face[column] = NO;
		return (distance_hor);
	}
	else
	{
		data->wall.wall_hit[column] = intersection->intersection_ver_y;
		if (is_ray_facing_right(ray_angle))
			data->wall.wall_face[column] = WE;
		else
			data->wall.wall_face[column] = EA;
		return (distance_ver);
	}
}

// calculate the correct distances for each ray
void	cast_all_rays(t_player *player, t_cub3d *data)
{
	int				column;
	float			correct_distance;
	float			distorted_distance;
	float			ray_angle;
	t_intersection	intersection;

	column = 0;
	while (column < PP_WIDTH)
	{
		ray_angle = get_absolute_ray_angle(column, player);
		find_wall(player, data, ray_angle, &intersection);
		distorted_distance = find_and_set_wall_data(data, column, ray_angle,
				&intersection);
		correct_distance = distorted_distance
			* cosf(get_ray_angle_from_center(column));
		data->wall.distances[column] = correct_distance;
		column++;
	}
}

/*calculate the projected wall height based on the actual wall height
and distance to it */
void	calculate_wall_height(t_cub3d *data)
{
	float	dist_to_wall;
	int		projected_wall_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		column;

	column = 0;
	while (column < PP_WIDTH)
	{
		dist_to_wall = data->wall.distances[column];
		projected_wall_height = (int)((GRID_SIZE / dist_to_wall)
				* distance_to_projection_plane());
		data->wall.wall_height[column] = projected_wall_height;
		wall_top_pixel = (PP_HEIGHT / 2) - (projected_wall_height / 2);
		wall_bottom_pixel = (PP_HEIGHT / 2) + (projected_wall_height / 2);
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		if (wall_bottom_pixel >= PP_HEIGHT)
			wall_bottom_pixel = PP_HEIGHT - 1;
		data->wall.top[column] = wall_top_pixel;
		data->wall.bottom[column] = wall_bottom_pixel;
		column++;
	}
}
