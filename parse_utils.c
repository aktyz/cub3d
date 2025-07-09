/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:40:48 by zslowian          #+#    #+#             */
/*   Updated: 2025/07/09 12:42:05 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_store_rgb(unsigned int color_storage[3], char **color_values);
bool	ft_validate_map_line_len(int *map_len, t_token *map_token);

void	ft_store_rgb(unsigned int color_storage[3], char **color_values)
{
	int		i;

	i = -1;
	while (++i < 3)
		color_storage[i] = ft_atoi((const char *)color_values[i]);
}

/**
 * Function checks if all map lines have the same length. It returns:
 * - false - if the map line length differ
 * - true - if the map line length is ok
 *
 */
bool	ft_validate_map_line_len(int *map_len, t_token *map_token)
{
	if (*map_len == -1)
		*map_len = ft_strlen(map_token->value);
	else if (ft_strlen(map_token->value) < 3)
		return (false);
	return (true);
}
