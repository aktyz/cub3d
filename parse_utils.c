/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:19:30 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/20 22:31:19 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_finish_parsing_checks(t_cub3d *data)
{
	if (data->map_cols < 3)
		ft_error(WRONG_MAP, "ft_parse - map has too few columns", data);
	if (!data->textures->no_texture || !data->textures->so_texture
		|| !data->textures->we_texture || !data->textures->ea_texture)
		ft_error(WRONG_MAP, "one or more textures missing", data);
	if (!are_all_colors(data))
		ft_error(WRONG_MAP, "one or two color values missing", data);
}

bool	ft_populate_token_value(t_token *last, char *line, int char_count,
			int k)
{
	last->value = ft_calloc(sizeof(char), char_count + 1);
	if (!last->value)
		return (true);
	ft_strlcpy(last->value, &line[k], char_count);
	return (false);
}
