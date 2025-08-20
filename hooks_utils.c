/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:25:37 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/20 11:22:27 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Summary of the Fix
The problem was that your original collision detection only checked if the center point of the player would hit a wall. This approach had a critical flaw: when dealing with diagonal wall patterns, the player could squeeze through gaps because their collision detection didn't account for their physical size.

What the fix does:
1. Player Radius: The fix introduces a player_radius that is 30% of a grid cell size (GRID_SIZE * 0.3f). This gives the player a reasonable physical size for collision detection.

2. Four-Point Collision Detection: Instead of checking just the center point, the new code checks four corner points around the player's bounding box:
- Top-left corner: (new.x - player_radius, new.y - player_radius)
- Top-right corner: (new.x + player_radius, new.y - player_radius)
- Bottom-left corner: (new.x - player_radius, new.y + player_radius)
- Bottom-right corner: (new.x + player_radius, new.y + player_radius)

3. Comprehensive Wall Checking: For each of these four points, the code:
- Converts the float coordinates to grid coordinates
- Checks if the grid position is within map bounds
- Checks if the grid position contains a wall ('1')

4. Movement Prevention: If any of the four corner points would hit a wall or go out of bounds, the movement is completely prevented.

This creates much more realistic and robust collision detection that prevents wall clipping while still allowing smooth movement through legitimate pathways.
 */

//collision check, update player's position
void	ft_update_player_pos(t_cub3d *data, t_float_position new)
{
	float	player_radius;
	int		check_points[4][2];
	int		i;

	player_radius = GRID_SIZE * 0.15f;
	check_points[0][0] = (int)((new.x - player_radius) / GRID_SIZE); // top-left x
	check_points[0][1] = (int)((new.y - player_radius) / GRID_SIZE); // top-left y
	check_points[1][0] = (int)((new.x + player_radius) / GRID_SIZE); // top-right x
	check_points[1][1] = (int)((new.y - player_radius) / GRID_SIZE); // top-right y
	check_points[2][0] = (int)((new.x - player_radius) / GRID_SIZE); // bottom-left x
	check_points[2][1] = (int)((new.y + player_radius) / GRID_SIZE); // bottom-left y
	check_points[3][0] = (int)((new.x + player_radius) / GRID_SIZE); // bottom-right x
	check_points[3][1] = (int)((new.y + player_radius) / GRID_SIZE); // bottom-right y
	i = -1;
	while (++i < 4)
	{
		if (check_points[i][1] < 0 || check_points[i][1] >= data->map_rows ||
			check_points[i][0] < 0 || check_points[i][0] >= data->map_cols ||
			data->map[check_points[i][1]][check_points[i][0]] == '1')
				return; // Collision detected, don't move
	}
	data->player.player_x = new.x;
	data->player.player_y = new.y;
}
