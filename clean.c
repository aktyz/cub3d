/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:18:52 by zslowian          #+#    #+#             */
/*   Updated: 2025/07/25 16:56:28 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_clean(t_cub3d *data);

/**
 * Function used just before exiting the program, it assures no leaks
 * exits in our cub3d.
 *
 */
void	ft_clean(t_cub3d *data)
{
	if (!data)
		return ;
	if (data->infile_fd >= 0)
		close(data->infile_fd);
	free(data);
}
