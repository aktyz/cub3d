/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:02:02 by zslowian          #+#    #+#             */
/*   Updated: 2025/05/21 16:34:16 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# include "libft/headers/libft.h"
# include "minilibx-linux/mlx.h"
# include "math.h"

typedef struct s_player_position
{
	int height; //half of grid size = 32 (looks good on the screen)
	int fov; //how many degrees - 60 
	int position_x;
    int position_y;
	int distance_to_projection_plane; // calculated after each movement
}	t_player_position;


typedef struct s_projection_plane
{
	//dimensions of the projection plane = 320 x 200 (resolution of most VGA video cards)
	//grid_height = 64

	int x;
	int y;

} t_projection_plane;

#endif
