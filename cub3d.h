/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:02:02 by zslowian          #+#    #+#             */
/*   Updated: 2025/07/09 12:42:43 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/headers/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>

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
}	t_cub3d;

typedef struct s_token
{
	t_cub3d_token_types	data_id;
	char				*value;
} t_token;

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

// PARSING
void	ft_parse(t_cub3d *data);
void	ft_store_rgb(unsigned int color_storage[3], char **color_values);

// MAP VALIDATION
bool	ft_is_alphanumeric(char *token);
bool	ft_validate_map_line_len(int *map_len, t_token *map_token);

// ERROR HANDLING
void	ft_error(t_cub3d_errors nb, char *ft_name, t_cub3d *data);

// CLEAN-UP
void	ft_clean(t_cub3d *data);

// DEBUGGING
void	ft_print_token_list(t_cub3d *data);
void	ft_print_map_player(t_cub3d *data);

#endif
