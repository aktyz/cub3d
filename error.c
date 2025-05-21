/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:49:46 by zslowian          #+#    #+#             */
/*   Updated: 2025/05/21 14:53:49 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const char	**ft_get_error_message(void);
void				ft_error(t_cub3d_errors nb, char *ft_name, t_cub3d *data);

/**
 * Function that let us have global error messages array,
 * without explicitly using global variable.
 *
 * - Prefix your message with ": "
 * - Suffix your message with "'\n'
 *       so that it prints nicely
 */
static const char	**ft_get_error_message(void)
{
	static const char	*e_msg[ERROR_NB];
	
	e_msg[1] = ": Provide only one argument: .cub file\n";
	e_msg[2] = ": Memory allocation error\n";
	return (e_msg);
}

/**
 * Error and exit function for our program, it:
 * 1. prints error message
 * 2. cleans program memory to avoid leaks [TODO]
 * 3. exits cub3d
 *
 */
void	ft_error(t_cub3d_errors nb, char *ft_name, t_cub3d *data)
{
	char	*msg;

	// print error message
	if (nb < ERROR_NB)
		msg = ft_strjoin(ft_name, ft_get_error_message()[nb]);
	else
		msg = ft_strjoin(ft_name, ": Unknown error\n");
	write(2, msg, ft_strlen(msg));
	(void) data;
	//ft_clean(&data);
	exit(EXIT_FAILURE);
}
