/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:02:02 by zslowian          #+#    #+#             */
/*   Updated: 2025/05/24 18:46:45 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# include "libft/headers/libft.h"
# include "minilibx-linux/mlx.h"
# include "math.h"
# include <mlx.h>
# include <stdlib.h>

#define SCREEN_HEIGHT 200 //units in this world
#define SCREEN_WIDTH 320
#define FOV_DEGREES 60
#define EXIT_FAILURE 

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

typedef struct s_window
{
	void *mlx_connection;
	void *mlx_window;
	t_img	image;
} t_fractal;

typedef struct s_player
{
	float p_x;
	float p_y;
}	t_player

typedef struct s_img
{
	void	*img_ptr; // pointer to image struct
	char	*pix_ptr;
	int		bpp; // bits per pixel
	int		endian;
	int		line_len;
}	t_img;

#endif


//Function prototypes

//init_window.c
void	ft_malloc_error(void);
void window_init(t_projection_plane *projection_plane);

//distance_to_pp.c
float degrees_to_radians(float degrees);
float get_angle_from_center(int column_number);
float distance_to_pp(int degree);