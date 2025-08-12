/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:49:46 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/12 15:15:14 by zslowian         ###   ########.fr       */
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
 * - Suffix your message with new line "\n"
 *       so that it prints nicely
 */
static const char	**ft_get_error_message(void)
{
	static const char	*e_msg[ERROR_NB];

	e_msg[1] = ": Provide only one argument: .cub file\n";
	e_msg[2] = ": Memory allocation error\n";
	e_msg[3] = ": Provided file has wrong format: .cub expected\n";
	e_msg[4] = ": File opening error (doesn't exist?)\n";
	e_msg[5] = ": There is a problem with token creation - check input data\n";
	e_msg[6] = ": There is a problem with parsing - check input data\n";
	e_msg[7] = ": Problem with input file closing\n";
	return (e_msg);
}

/**
 * Error and exit function for our program, it:
 * 1. prints error message
 * 2. cleans program memory to avoid leaks
 * 3. exits cub3d
 *
 * If you are in a hurry and don't want to add docs for new error
 * call this function with nb = ERROR_NB to log unknown error
 */
void	ft_error(t_cub3d_errors nb, char *ft_name, t_cub3d *data)
{
	char	*msg;

	if (nb > 0 && nb < ERROR_NB)
		msg = ft_strjoin(ft_name, ft_get_error_message()[nb]);
	else
		msg = ft_strjoin(ft_name, ": Unknown error\n");
	write(2, "Error:\t", ft_strlen("Error:\t"));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	ft_clean(data);
	free(msg);
	exit(EXIT_FAILURE);
}
