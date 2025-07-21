/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:02:02 by zslowian          #+#    #+#             */
/*   Updated: 2025/07/24 20:32:11 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "math.h"
# include <stdlib.h>
# include "libft/headers/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <float.h>
#include <stdbool.h>


#define SCREEN_HEIGHT 200.0f //dimensions of the window/screen in pixels
#define SCREEN_WIDTH 320.0f //the number of columns to be rendered - how many rays will be cast
#define CENTER_OF_PP_HEIGHT 100.0f //used for placing the wall - the center of each wall will be on this horizontal line
#define CENTER_OF_PP_WIDTH 170.0f //not sure whether it will be used yet
#define FOV 60.0f  //field of view - a float literal
#define FOV_RAD (FOV * M_PI / 180.0f)  //fov in radians
#define GRID_SIZE 64
#define INFINITY FLT_MAX
#define EPSILON 0.0001f //a small value for float comparisons


typedef enum e_cub3d_token_types
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	DATA_ID_NB,
	MAP,
	TOKEN_TYPE_NB,
} t_cub3d_token_types;

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
	TOKENIZING_ERROR,
	ERROR_WHEN_PARSING,
	FILE_CLOSE,
	WRONG_MAP,
	ERROR_NB,
}	t_cub3d_errors;

typedef struct s_file_names
{
	char *no_texture;
	char *so_texture;
	char *we_texture;
	char *ea_texture;
}	t_file_names;

/**
 * To simplyfy the allocation and freeing the memory, we store
 * rgb color values in an unsigned int array where:
 * _color[0] - is r value
 * _color[1] - is g value
 * _color[2] - is b value
 *
 */
typedef struct s_colors
{
	unsigned int	floor_color[3];
	unsigned int	ceiling_color[3];
}	t_colors;

typedef struct s_player
{
	int		start_row;
	int		start_col;
	char	orientation;
}	t_player;
/**
 * Global cub3d data representation.
 * First part is representing static information passed from the infile
 * Second part is representing MiniLibX pointers so that we are able to clean
 * render data nicely when exiting the program.
 *
 */
typedef struct s_cub3d
{
	int				infile_fd;
	t_list			*tokens;
	t_file_names	*textures;
	t_colors		*colors;
	char			**map;
	t_player		player;
	int				map_rows;
	int				map_cols;
}	t_cub3d;


typedef struct s_player_position
{
	t_cub3d_token_types	data_id;
	char				*value;
} t_token;

typedef struct s_token
{
	char	*data_id;
	char	*value;
} t_token;

typedef struct s_window
{
	void *mlx_connection;
	void *mlx_window;
	t_img	image;
} t_window;

typedef struct s_player
{
	int height; //half of grid size = 32 (looks good on the screen)
	int fov; //how many degrees - 60 
	float player_x; //worls coordinates of a player
	float player_y;
	float player_angle; //player's viewing angle in radians, which direction he is looking at
	//0 degrees - east, 90 degrees or M-PI / 2.0 radians - North
}	t_player;

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
    //float	distances[SCREEN_WIDTH]; //distances for each ray
	//int		wall_height[SCREEN_WIDTH]; //this is in t_wall from now on - to be removed
	t_wall	*wall;
} t_game_data;

typedef struct s_intersection
{
    float intersection_hor_x;
    float intersection_hor_y;
    float intersection_ver_x;
    float intersection_ver_y;
    float distance_to_wall_hor;
    float distance_to_wall_ver;
} t_intersection;

typedef struct t_wall
{
	float	distances[SCREEN_WIDTH]; //distances for each ray
	int		wall_height[SCREEN_WIDTH];
	int		top[SCREEN_WIDTH];
	int		bottom[SCREEN_WIDTH];
}	t_wall;




// DEBUGGING
void	ft_print_token_list(t_cub3d *data);
void	ft_print_map_player(t_cub3d *data);

// INITIALIZATION
void	ft_init(char *file_name, t_cub3d *data);

// TOKEN CREATION
void	ft_tokenize(t_cub3d *data);
void	ft_add_map_token(int *i, char *line, t_cub3d *data);

// PARSING
void	ft_parse(t_cub3d *data);
void	ft_store_rgb(unsigned int color_storage[3], char **color_values);
void	ft_copy_map_token_to_struct(char *map_line, int *map_row,
			t_cub3d *data);

// MAP VALIDATION
bool	ft_is_alphanumeric(char *token);

// ERROR HANDLING
void	ft_error(t_cub3d_errors nb, char *ft_name, t_cub3d *data);

// CLEAN-UP
void	ft_clean(t_cub3d *data);


//init_window.c
void	ft_malloc_error(void);
void window_init(t_projection_plane *projection_plane);

//distance_to_pp.c
float degrees_to_radians(float degrees);
float get_angle_from_center(int column_number);
float distance_to_pp(int degree);

//ray_angles.c
float	degrees_to_radians(float degrees);
float	get_absolute_ray_angle(int column, t_player *player);
float	get_ray_angle_from_center(int column);
float	distance_to_projection_plane(void);

//check_horizontal.c
int		is_ray_facing_up(float ray_angle);
float	find_first_horizontal_intersection_y(t_player player, float ray_angle);
float	find_first_horizontal_intersection_x(t_player player, float ray_angle);
float	find_horizontal_step_y(float ray_angle);
float	find_horizontal_step_x(float ray_angle);

//check_vertical.c
int		is_ray_facing_right(float ray_angle);
int		is_ray_vertical(float ray_angle);
float	find_first_vertical_intersection_x(t_player player, float ray_angle);
float	find_first_vertical_intersection_y(t_player player, float ray_angle, float first_intersection_x);
float	find_vertical_step_x(float ray_angle);
float	find_vertical_step_y(float ray_angle);

//render_loop.c
int		is_wall_on_grid(float intersection_x, float intersection_y, t_game_data *data);
float	distance_to_the_wall(t_player *player, int column, float intersection_x, float intersection_y);
void	find_wall(t_player player, t_game_data *data, float ray_angle, t_intersection *intersection);
float	smaller_distance_wall(t_player player, int columm, t_intersection *intersection);
void	cast_all_rays(t_player player, t_game_data *data, float ray_angle, t_intersection *intersection);


#endif
