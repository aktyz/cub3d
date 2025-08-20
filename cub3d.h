/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:02:02 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/20 15:38:25 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/headers/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include "math.h"
# include <stdlib.h>
# include <float.h>
# include <stdbool.h>
# include <X11/keysym.h>

#define PP_HEIGHT 200 //height of the projection plane in pixels (screen)
#define PP_WIDTH 320 //width of the projection plane in pixels (screen) - how many rays will be cast
#define FOV 60.0f  //field of view - a float literal
#define FOV_RAD (FOV * M_PI / 180.0f)  //fov in radians
#define GRID_SIZE 64
#define EPSILON 0.0001f //a small value for float comparisons
#define WIN_WIDTH (PP_WIDTH * SCALE) //width of the scaled window
#define WIN_HEIGHT (PP_HEIGHT * SCALE) //height of the scaled window
#define SCALE 2 //scale (3 * dimensions of projection plane)
#define MOVE_SPEED 4.0f //how fast a player moves (ASWD keys)
#define ROTATION_SPEED (M_PI / 90.0f) //how fast a player rotates (left/right arrow keys)
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define COLOR_INIT_VALUE -1

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
	COLOR,
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
	int	floor_color[3];
	int	ceiling_color[3];
}	t_colors;

typedef struct s_player
{
	//map coordinates of a player
	int		start_row;
	int		start_col;
	char	orientation;

	//world coordinates of a player
	float player_x;
	float player_y;
	float player_angle; //player's absolute viewing angle (0 - East, PI/2 - North)

}	t_player;

typedef struct s_img
{
	void	*img_ptr; //pointer to image struct
	char	*pix_ptr;
	int		bpp; //bits per pixel
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_texture_data
{
	t_img	img;
	int		width;
	int		height;
}	t_texture_data;

typedef struct s_wall
{
	float	distances[PP_WIDTH]; //actual distances from player to the wall hit for each ray
	int		wall_height[PP_WIDTH]; //the projected wall height for each ray
	int		top[PP_WIDTH]; //y coordinate of a place, where the top of the wall should be drawn
	int		bottom[PP_WIDTH]; //y coordinate of a place, where the bottom of the wall should be drawn

	t_cub3d_token_types	wall_face[PP_WIDTH];
	float			wall_hit[PP_WIDTH];
}	t_wall;

typedef struct s_intersection
{
    float intersection_hor_x; //x coordinate of the intersection between the cast ray and horizontal grid line
    float intersection_hor_y; //y coordinate of the intersection between the cast ray and horizontal grid line
    float intersection_ver_x; //x coordinate of the intersection between the cast ray and vertical grid line
    float intersection_ver_y; //y coordinate of the intersection between the cast ray and vertical grid line
    float distance_to_wall_hor;
    float distance_to_wall_ver;
} t_intersection;


typedef struct s_input
{
	bool	turn_left;
	bool	turn_right;
	bool	move_right;
	bool	move_left;
	bool	move_forward;
	bool	move_backward;
}	t_input;


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
	int				map_rows;
	int				map_cols;
	t_texture_data	textures_data[4];

	//mlx data
	void			*mlx;
	void			*win;
	t_img			image;

	//keys input
	t_input input;


	//game_state
	t_player		player;
	t_wall			wall;
	t_intersection	intersection;
}	t_cub3d;

typedef struct s_token
{
	t_cub3d_token_types	data_id;
	char				*value;
} t_token;

typedef struct s_float_position
{
	float	x;
	float	y;
} t_float_position;

// INITIALIZATION
void	ft_init(char *file_name, t_cub3d *data);

// TOKEN CREATION
void	ft_tokenize(t_cub3d *data);
void	ft_add_map_token(int *i, char *line, t_cub3d *data);

// PARSING
void	ft_parse(t_cub3d *data);
void	ft_copy_map_token_to_struct(char *map_line, int *map_row,
			t_cub3d *data);
void	ft_finish_parsing_checks(t_cub3d *data);

// COLORS
void	ft_store_rgb(int color_storage[3], char **color_values,
			t_cub3d *data);
bool	are_all_colors(t_cub3d *data);
void	init_colors(t_cub3d *data);

// MAP VALIDATION
bool	ft_is_alphanumeric(char *token);
bool	ft_is_map_valid(t_cub3d *data);
char	**ft_copy_map(t_cub3d *data, int map_rows, int map_cols);
void	ft_free_map_copy(char **map_copy, int map_rows);
void	ft_switch_remaining_zeroes(char **map_copy, t_cub3d *data);

// ERROR HANDLING
void	ft_error(t_cub3d_errors nb, char *ft_name, t_cub3d *data);

// CLEAN-UP
void	ft_clean(t_cub3d *data);

// DEBUGGING
void	ft_print_token_list(t_cub3d *data);
void	ft_print_map_player(t_cub3d *data);
void	ft_print_map(char **map, int map_rows);

//ray_angles.c
float	degrees_to_radians(float degrees);
float	get_absolute_ray_angle(int column, t_player *player);
float	get_ray_angle_from_center(int column);
float	distance_to_projection_plane(void);

//check_horizontal.c
int		is_ray_facing_up(float ray_angle);
float	find_first_horizontal_intersection_y(t_player *player, float ray_angle);
float	find_first_horizontal_intersection_x(t_player *player, float ray_angle);
float	find_horizontal_step_y(float ray_angle);
float	find_horizontal_step_x(float ray_angle);

//check_vertical.c
int		is_ray_facing_right(float ray_angle);
int		is_ray_vertical(float ray_angle);
float	find_first_vertical_intersection_x(t_player *player, float ray_angle);
float	find_first_vertical_intersection_y(t_player *player, float ray_angle);
float	find_vertical_step_x(float ray_angle);
float	find_vertical_step_y(float ray_angle);

//cast_rays.c
int		is_wall_on_grid(float intersection_x, float intersection_y, t_cub3d *data);
float	distance_to_the_wall(t_player *player, int column, float intersection_x, float intersection_y);
void	find_wall(t_player *player, t_cub3d *data, float ray_angle, t_intersection *intersection);
void	cast_all_rays(t_player *player, t_cub3d *data);
void	calculate_wall_height(t_cub3d *data);

//game_loop.c
void	setup_player_and_map(t_cub3d *game);
int		game_loop(t_cub3d *game);
void	ft_pixel_put(t_img *image, int x, int y, int color);
void	draw_frame(t_cub3d *data);

//init_mlx.c
void init_mlx(t_cub3d *data);
void render_scaled_frame(t_cub3d *data);
unsigned int get_pixel_color(t_img *image, int x, int y);

//hooks.c
int		handle_keypress(int keycode, t_cub3d *data);
int		handle_keyrelease(int keycode, t_cub3d *data);
int		close_game(t_cub3d *data);
void	look_left(t_cub3d *data);
void	look_right(t_cub3d *data);
void	move_right(t_cub3d *data);
void	move_left(t_cub3d *data);
void	move_forward(t_cub3d *data);
void	move_backward(t_cub3d *data);
void	ft_update_player_pos(t_cub3d *data, t_float_position new);

//textures.c
unsigned int get_texture_pixel_color(t_texture_data *texture, int x, int y);
void load_single_texture(t_cub3d *data, t_texture_data *tex_data, char *path);
void load_textures(t_cub3d *data);


#endif
