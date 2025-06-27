/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:55:26 by zslowian          #+#    #+#             */
/*   Updated: 2025/06/19 17:50:06 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_init(char *file_name, t_cub3d *data);
static void	ft_validate_input_file(char *file_name, t_cub3d *data);

/**
 * Function initializing the program and performing initial setup:
 * 1. Validate the input file and open its file descriptor
 * 2. (Future) Parse the map
 * 3. (Future) Validate the map
 *
 * TBD: parsing and validation can happen simultaneously
 */
void	ft_init(char *file_name, t_cub3d *data)
{
	//t_list	*tokens;

	data->infile_fd = -1;
	ft_validate_input_file(file_name, data);
	ft_tokenize(data);
	ft_print_token_list(data);
	ft_parse(data);
	//ft_parse(data);
}

/**
 * Function checks if user provided correct file format and if yes,
 * opens the fd to read from, fd is stored in the global data structure.
 */
static void	ft_validate_input_file(char *file_name, t_cub3d *data)
{
	char	*extension;

	extension = ft_strrchr(file_name, '.');
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0)
		ft_error(FF_ERROR, "ft_validate_input_file", data);
	data->infile_fd = open(file_name, O_RDONLY);
	if (data->infile_fd < 0)
		ft_error(OPEN_ERROR, "ft_validate_input_file", data);
}
