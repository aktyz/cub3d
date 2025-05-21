/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:02:02 by zslowian          #+#    #+#             */
/*   Updated: 2025/05/21 17:38:41 by zslowian         ###   ########.fr       */
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
 * First part is reprsenting static information passed from the infile
 * Second part is representig MiniLibX pointer so that we are able to clean
 * them nicely when exiting the program.
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

#endif
