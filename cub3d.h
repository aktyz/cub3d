/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:02:02 by zslowian          #+#    #+#             */
/*   Updated: 2025/05/27 00:56:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# include "libft/headers/libft.h"
# include "minilibx-linux/mlx.h"
# include "math.h"
# include <mlx.h>
# include <stdlib.h>

#define SCREEN_HEIGHT 200 //dimensions of the window/screen in pixels
#define SCREEN_WIDTH 320 //the number of columns to be rendered - how many rays will be cast
#define FOV_DEGREES 60
#define GRID_SIZE 64
#define EXIT_FAILURE 

typedef struct s_player_position
{
	int height; //half of grid size = 32 (looks good on the screen)
	int fov; //how many degrees - 60 
	// int position_x; //for raycasting i use mostly t_player, probably not needed here then
    // int position_y;
	// int distance_to_projection_plane; // calculated 
}	t_player_position;

//it is defined as macro - will it be needed? probably not
// typedef struct s_projection_plane
// {
// 	//dimensions of the projection plane = 320 x 200 (resolution of most VGA video cards)
// 	//grid_height = 64

// 	int x;
// 	int y;

// } t_projection_plane;

typedef struct s_window
{
	void *mlx_connection;
	void *mlx_window;
	t_img	image;
} t_fractal;

typedef struct s_player
{
	float p_x; //worls coordinates of a player
	float p_y;
	float angle_in_rad; //player's viewing angle in radians
}	t_player

typedef struct s_img
{
	void	*img_ptr; //pointer to image struct
	char	*pix_ptr;
	int		bpp; //bits per pixel
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_game_data
{
    t_player	player;
    t_player_view_settings 	player_view; // For FOV etc.
    char	**map; //the 2D game - map[x][y]
    int		map_width_grid;  //map width in number of grid cells
    int		map_height_grid; //map height in number of grid cells
    void	*mlx_connection; //taken from t_window
	void	*mlx_window;     //fromt_window
	t_img	image;          //from t_window
    float	distances[SCREEN_WIDTH]; //distances for each ray
} t_game_data;

#endif


//Function prototypes

//init_window.c
void	ft_malloc_error(void);
void window_init(t_projection_plane *projection_plane);

//distance_to_pp.c
float degrees_to_radians(float degrees);
float get_angle_from_center(int column_number);
float distance_to_pp(int degree);