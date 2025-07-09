/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:42:30 by zslowian          #+#    #+#             */
/*   Updated: 2025/07/09 12:42:11 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_add_map_token(int *i, char *line, t_cub3d *data);
void		ft_copy_map_token_to_struct(char *map_line, int *map_row,
				t_cub3d *data);
static bool	ft_validate_map_char(char map_char, bool *is_player);

/**
 * Function run basic check on string read from the .cub file
 * and adds the valid ones to the token list with MAP token type.
 *
 */
void	ft_add_map_token(int *i, char *line, t_cub3d *data)
{
	char	*ptr;
	int		char_count;
	t_token	*new;

	ptr = &line[*i];
	char_count = 0;
	while (*ptr)
	{
		char_count++;
		ptr++;
	}
	if (char_count && ft_is_alphanumeric(&line[*i]))
	{
		new = ft_calloc(sizeof(t_token), 1);
		new->value = ft_calloc(sizeof(char), char_count + 1);
		ft_strlcpy(new->value, &line[*i], char_count);
		new->data_id = MAP;
		ft_lstadd_back(&data->tokens, ft_lstnew(new));
		data->map_rows++;
	}
	*i += char_count;
}

/**
 * Function takes the string of map_line, run additional character checks
 * on it and then if all good copies it to the data->map 2D array which can be
 * then used in the process of raycasting.
 * Function also checks if there's a player position available in the map
 * file.
 */
void	ft_copy_map_token_to_struct(char *map_line, int *map_row,
			t_cub3d *data)
{
	bool	is_player;
	char	*ptr;
	int		char_pos;

	is_player = false;
	ptr = map_line;
	char_pos = 0;
	data->map[*map_row] = ft_calloc(ft_strlen(map_line), sizeof(char));
	if (!data->map[*map_row])
		ft_error(MEM_ERROR, "ft_copy_map_token_to_struct", data);
	while (*ptr)
	{
		if (!ft_validate_map_char(*ptr, &is_player))
			ft_error(WRONG_MAP, "ft_save_map - map contains wrong chars", data);
		data->map[*map_row][char_pos] = *ptr;
		if (is_player)
		{
			if (data->player.orientation)
				ft_error(WRONG_MAP, "ft_copy_map_token_to_struct - more than one player", data);
			data->player.start_row = *map_row;
			data->player.start_col = char_pos;
			data->player.orientation = *ptr;
			is_player = false;
		}
		ptr++;
		char_pos++;
	}
	*map_row = *map_row + 1;
}

/**
 * Function checks if map character is valid. It returns:
 * - false - if there's a forbidden char
 * - true - if char belong to the correct set
 *
 */
static bool	ft_validate_map_char(char map_char, bool *is_player)
{
	if (map_char == ' ' || map_char == '0' || map_char == '1')
		return (true);
	if (map_char == '\n')
		return (true);
	if (map_char == 'N' || map_char == 'S')
	{
		*is_player = true;
		return (true);
	}
	if (map_char == 'E' || map_char == 'W')
	{
		*is_player = true;
		return (true);
	}
	return (false);
}
