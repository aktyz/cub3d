/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:55:26 by zslowian          #+#    #+#             */
/*   Updated: 2025/05/21 17:39:15 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_init(char *file_name, t_cub3d *data);
static void	ft_validate_input_file(char *file_name, t_cub3d *data);

/**
 * Function initializing the whole program and populating the data for it:
 * 1. allocate the program data
 *     - `tokens` list content is simply `char *`
 * 2. parse map
 * 3. validate the map
 * 
 * TBD: parsing and validation can happen simultaniously
 */
void	ft_init(char *file_name, t_cub3d *data)
{
	//t_list	*tokens;

	data->infile_fd = -1;
	ft_validate_input_file(file_name, data);
	//ft_tokenize(data);
	//ft_parse(data);
}

/**
 * Function checks if user provided correct file format and if yes,
 * opens the fd to read from stored in the global data structure.
 */
static void	ft_validate_input_file(char *file_name, t_cub3d *data)
{
	char	*ptr;

	ptr = file_name;
	if (*ptr == '.')
		ptr++;
	while (*ptr && *ptr != '.')
		ptr++;
	if ((*ptr && ft_strncmp(ptr, ".cub", 5) != 0) || !ptr)
		ft_error(FF_ERROR, "ft_validate_input_file", data);
	data->infile_fd = open(file_name, O_RDONLY);
	if (data->infile_fd < 0)
		ft_error(OPEN_ERROR, "ft_validate_input_file", data);
}
