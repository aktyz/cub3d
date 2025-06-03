/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:02:02 by zslowian          #+#    #+#             */
/*   Updated: 2025/06/03 16:35:47 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/headers/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>

/**
 * Structure (enumeration) of our cub3d possible errors.
 * It is later used by error handling functions to determine
 * the right message to be printed in the terminal.
 *
 * In order to add new error type, insert the desired error
 * enum symbol **before** `ERROR_NB`.
 * In order to associate a message to your new type of error,
 * update `ft_get_error_message()` function with your new error message.
 *
 */
typedef enum e_cub3d_errors
{
	NO_ERROR,
	MAIN_ARGS,
	MEM_ERROR,
	FF_ERROR,
	OPEN_ERROR,
	ERROR_NB,
}	t_cub3d_errors;
/**
 * Structure to represent a color in our program
 *
 */
typedef struct s_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_color;

/**
 * Global cub3d data representation.
 * First part is representing static information passed from the infile
 * Second part is representing MiniLibX pointers so that we are able to clean
 * render data nicely when exiting the program.
 *
 */
typedef struct s_cub3d
{
	int		infile_fd;
	t_list	*textures;
	t_color	*floor_color;
	t_color	*ceiling_color;
}	t_cub3d;

// INITIALIZATION
void	ft_init(char *file_name, t_cub3d *data);

// ERROR HANDLING
void	ft_error(t_cub3d_errors nb, char *ft_name, t_cub3d *data);

// CLEAN-UP
void	ft_clean(t_cub3d *data);
# include "math.h"
# include <mlx.h>
# include <stdlib.h>
# include <float.h>

#define SCREEN_HEIGHT 200 //dimensions of the window/screen in pixels
#define SCREEN_WIDTH 320 //the number of columns to be rendered - how many rays will be cast
#define FOV_DEGREES 60.0f  //a float literal
#define FOV_RAD (FOV_DEGREES * M_PI / 180.0f)  //fov in radians
#define GRID_SIZE 64
#define EXIT_FAILURE 
#define INFINITY FLT_MAX
#define EPSILON 0.0001f //a small value for float comparisons

typedef struct s_player_position
{
	int height; //half of grid size = 32 (looks good on the screen)
	int fov; //how many degrees - 60 
	// int position_x; //for raycasting i use mostly t_player, probably not needed here then
    // int position_y;
	// int distance_to_projection_plane; // calculated 
}	t_player_position;


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


//the two below still unused yet
//a structure for the result of a DDA check along one axis (horizontal or vertical)
typedef struct s_axis_hit 
{
    float   dist;   //distance to the hit point
    float   hit_x;  //x-coordinate of the hit
    float   hit_y;  //y-coordinate of the hit
} t_axis_hit;

//struct for infomration about a ray's intersection with a wall
typedef struct s_ray_hit_info 
{
    float   distance;           //final (corrected) distance to the wall
    float   raw_distance;       //uncorrected distance (useful for some calcs)
    float   hit_x;              //x-coordinate of the wall hit
    float   hit_y;              //y-coordinate of the wall hit
    int     was_horizontal_hit; // 1 if hit a horizontal segment, 0 if vertical, -1 if no hit
    //maybe for the future - wall orientation like NORTH, SOUTH, EAST, WEST
} t_ray_hit_info;

#endif


//Function prototypes

//init_window.c
void	ft_malloc_error(void);
void window_init(t_projection_plane *projection_plane);

//distance_to_pp.c
float degrees_to_radians(float degrees);
float get_ray_angle(int column, float player_angle_rad);
float distance_to_pp(int degree);