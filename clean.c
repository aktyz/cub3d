/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:18:52 by zslowian          #+#    #+#             */
/*   Updated: 2025/05/21 17:38:06 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_clean(t_cub3d *data);

/**
 * Function used just before exiting the program, it assures no leaks
 * available.
 *
 */
void	ft_clean(t_cub3d *data)
{
	if (!data)
		return ;
	if (data->infile_fd >= 0)
	{
		close(data->infile_fd);
		data->infile_fd = -1;
	}
	if (data)
		free(data);
	data = NULL;
}
