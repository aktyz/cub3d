/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:02:02 by zslowian          #+#    #+#             */
/*   Updated: 2025/07/03 13:11:22 by zslowian         ###   ########.fr       */
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
	INVALID_MAP,
	FILE_CLOSE,
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

typedef struct s_file_names
{
	char *no_texture;
	char *so_texture;
	char *we_texture;
	char *ea_texture;
}	t_file_names;

typedef struct s_colors
{
	t_color	*floor_color;
	t_color	*ceiling_color;
}	t_colors;

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
	t_file_names	textures;
	t_colors		colors;
}	t_cub3d;

typedef struct s_token
{
	char	*data_id;
	char	*value;
} t_token;

// INITIALIZATION
void	ft_init(char *file_name, t_cub3d *data);

// TOKEN CREATION
void	ft_tokenize(t_cub3d *data);
void	ft_add_map_line(int *i, char *line, t_cub3d *data);

// PARSING
void	ft_parse(t_cub3d *data);

// MAP VALIDATION
bool	ft_is_alphanumeric(char *token);

// ERROR HANDLING
void	ft_error(t_cub3d_errors nb, char *ft_name, t_cub3d *data);

// CLEAN-UP
void	ft_clean(t_cub3d *data);

// DEBUGGING
void	ft_print_token_list(t_cub3d *data);

#endif
