/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_angles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:41:35 by hhurnik           #+#    #+#             */
/*   Updated: 2025/08/19 17:41:37 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// convert degrees to radians (for math functions)
float	degrees_to_radians(float degrees)
{
	return (degrees * (M_PI / 180.0f));
}

/*calculates the absolute value of an angle of a single ray 
(if player is looking North, the leftmost ray is 120 degrees)*/
float	get_absolute_ray_angle(int column, t_player *player)
{
	float	ray_angle;
	float	angle_from_center;
	float	column_from_center;

	column_from_center = column - (PP_WIDTH / 2.0f);
	angle_from_center = column_from_center * (FOV_RAD / PP_WIDTH);
	ray_angle = player->player_angle + angle_from_center;
	ray_angle = fmod(ray_angle, 2.0f * M_PI);
	if (ray_angle < 0)
	{
		ray_angle += 2.0f * M_PI;
	}
	return (ray_angle);
}

/*calculate the ray angle from the line going directly in front of 
the player (center) to this specific ray*/
float	get_ray_angle_from_center(int column)
{
	float	column_from_center;
	float	angle_from_center;

	column_from_center = (float)column - 159.5f;
	if (column_from_center < 0)
		column_from_center = floorf(column_from_center);
	else
		column_from_center = ceilf(column_from_center);
	angle_from_center = fabs(degrees_to_radians(column_from_center * (FOV
					/ PP_WIDTH)));
	return (angle_from_center);
}

// distance to projection plane is fixed
float	distance_to_projection_plane(void)
{
	float	half_fov_degrees;
	float	half_fov_radians;
	float	half_screen_width;
	float	distance;

	half_fov_degrees = FOV / 2.0f;
	half_fov_radians = degrees_to_radians(half_fov_degrees);
	half_screen_width = (float)PP_WIDTH / 2.0f;
	distance = half_screen_width / tanf(half_fov_radians);
	return (distance);
}
