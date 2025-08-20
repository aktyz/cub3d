/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ray_direction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:30:01 by hhurnik           #+#    #+#             */
/*   Updated: 2025/08/19 17:37:14 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//"up" means in the direction of the increasing y
int	is_ray_facing_up(float ray_angle)
{
	if (ray_angle > M_PI && ray_angle < (2.0f * M_PI))
		return (1);
	else
		return (0);
}

int	is_ray_horizontal(float ray_angle)
{
	if (fabsf(sinf(ray_angle)) < EPSILON)
		return (1);
	return (0);
}

int	is_ray_facing_right(float ray_angle)
{
	if ((ray_angle >= 0 && ray_angle < (M_PI / 2.0f)) || (ray_angle > (3.0f
				* M_PI / 2.0f) && ray_angle < (2.0f * M_PI)))
		return (1);
	if (fabsf(ray_angle) < 0.00001f
		|| fabsf((float)(ray_angle - 2.0f * M_PI)) < 0.00001f)
		return (1);
	return (0);
}

// check for vertical rays (cos(angle) is 0) - angle PI/2 or 3PI/2
int	is_ray_vertical(float ray_angle)
{
	if (fabsf(cosf(ray_angle)) < 0.00001f)
		return (1);
	return (0);
}
