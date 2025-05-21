/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:55:26 by zslowian          #+#    #+#             */
/*   Updated: 2025/05/21 14:53:02 by zslowian         ###   ########.fr       */
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
	
	data = ft_calloc(sizeof(t_cub3d), 1);
	if (data == NULL)
		ft_error(MEM_ERROR, "ft_init", data);
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
	(void)data;
	ft_printf("We are in ft_validate_input_file, file name: %s\n", file_name);
}