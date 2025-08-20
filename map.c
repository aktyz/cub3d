/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:42:30 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/20 22:09:34 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool		ft_add_map_token(int *i, char *line, t_cub3d *data);
void		ft_copy_map_token_to_struct(char *map_line, int *map_row,
				t_cub3d *data);
static bool	ft_validate_map_char(char map_char, bool *is_player);
static bool	ft_check_save_player_info(t_cub3d *data, int *map_row,
				int char_pos, char *map_line);
static void	ft_space_out_map_line(int *char_pos, int *map_row, t_cub3d *data);

/**
 * Function run basic check on string read from the .cub file
 * and adds the valid ones to the token list with MAP token type.
 *
 */
bool	ft_add_map_token(int *i, char *line, t_cub3d *data)
{
	char	*ptr;
	int		char_count;
	bool	is_error;

	ptr = &line[*i];
	char_count = 0;
	is_error = false;
	while (*ptr)
	{
		char_count++;
		ptr++;
	}
	if (char_count > data->map_cols)
		data->map_cols = char_count;
	if (char_count && ft_is_alphanumeric(&line[*i]))
		is_error = ft_new_map_token(data, char_count, line, i);
	*i += char_count;
	return (is_error);
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
	int		char_pos;

	is_player = false;
	char_pos = -1;
	data->map[*map_row] = ft_calloc(data->map_cols + 1, sizeof(char));
	if (!data->map[*map_row])
		ft_error(MEM_ERROR, "ft_copy_map_token_to_struct", data);
	while (++char_pos < data->map_cols)
	{
		if (!ft_validate_map_char(*map_line, &is_player))
			ft_error(WRONG_MAP,
				"ft_save_map - map contains wrong character", data);
		if (*map_line == '\n')
			ft_space_out_map_line(&char_pos, map_row, data);
		else
			data->map[*map_row][char_pos] = *map_line;
		if (is_player)
			is_player = ft_check_save_player_info(data, map_row,
					char_pos, map_line);
		map_line++;
	}
	data->map[*map_row][char_pos - 1] = '\0';
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
	bool	is_map;
	bool	is_white;

	is_map = (map_char == ' ' || map_char == '0');
	is_white = (map_char == '\n' || map_char == '1' || map_char == '\0');
	if (is_map || is_white)
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

static bool	ft_check_save_player_info(t_cub3d *data, int *map_row,
				int char_pos, char *map_line)
{
	if (data->player.orientation)
		ft_error(WRONG_MAP,
			"ft_copy_map_token_to_struct - more than one player", data);
	data->player.start_row = *map_row;
	data->player.start_col = char_pos;
	data->player.orientation = *map_line;
	return (false);
}

static void	ft_space_out_map_line(int *char_pos, int *map_row, t_cub3d *data)
{
	while (*char_pos < data->map_cols - 1)
	{
		data->map[*map_row][*char_pos] = ' ';
		*char_pos = *char_pos + 1;
	}
}
