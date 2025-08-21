/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:24:41 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/21 15:40:41 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool		ft_is_map_valid(t_cub3d *data);
static bool	ft_player_area_check(char **map_copy, int row, int col,
				t_cub3d *data);
static bool	ft_void_area_check(char **map_copy, t_cub3d *data);
static bool	ft_flood_fill_space(char **map_copy, int row, int col,
				t_cub3d *data);
static bool	ft_check_enclosure(char **map_copy, t_cub3d *data);
static bool	ft_flood_fill_zero(char **map_copy, int row, int col,
				t_cub3d *data);

/**
 * Function validating the map provided by the user.
 * It checks if the map is all surrounded by walls using
 * backtracking algorithm.
 * Return values:
 * - true if the map is valid
 * - false if there's a problem with the map
 *
 */
bool	ft_is_map_valid(t_cub3d *data)
{
	char	**map_copy;
	bool	is_valid;

	is_valid = true;
	map_copy = ft_copy_map(data, data->map_rows, data->map_cols);
	if (!map_copy)
		ft_error(MEM_ERROR, "ft_is_map_valid", data);
	if (!ft_player_area_check(map_copy, data->player.start_row,
			data->player.start_col, data))
		is_valid = false;
	if (!ft_check_enclosure(map_copy, data))
		is_valid = false;
	if (!ft_void_area_check(map_copy, data))
		is_valid = false;
	ft_free_map_copy(map_copy, data->map_rows);
	return (is_valid);
}

/**
 * Flood fill algorithm to check if all accessible areas are properly enclosed.
 * Returns false if the flood fill reaches the border of the map (invalid map).
 */
static bool	ft_player_area_check(char **map_copy, int row, int col,
		t_cub3d *data)
{
	if (row < 0 || row >= data->map_rows || col < 0 || col >= data->map_cols)
		return (false);
	if (map_copy[row][col] == '1' || map_copy[row][col] == 'X')
		return (true);
	if (map_copy[row][col] == ' ')
		return (false);
	if (map_copy[row][col] == '0' || map_copy[row][col] == 'N'
		|| map_copy[row][col] == 'S' || map_copy[row][col] == 'E'
		|| map_copy[row][col] == 'W')
	{
		map_copy[row][col] = 'X';
		return (ft_player_area_check(map_copy, row - 1, col, data)
			&& ft_player_area_check(map_copy, row + 1, col, data)
			&& ft_player_area_check(map_copy, row, col - 1, data)
			&& ft_player_area_check(map_copy, row, col + 1, data));
	}
	return (false);
}

/**
 * Function takes the copy of the map and whenever a space or
 * no char present on the map - it uses flood fill to check
 * if it is correctly surrounded by walls (1s) protecting player
 * from hitting the void area.
 */
static bool	ft_void_area_check(char **map_copy, t_cub3d *data)
{
	int		row;
	int		col;
	bool	result;

	row = -1;
	result = true;
	while (++row < data->map_rows)
	{
		col = -1;
		while (++col < data->map_cols)
		{
			if (map_copy[row][col] == ' ')
				result = ft_flood_fill_space(map_copy, row, col, data);
			if (result == false)
				return (false);
		}
	}
	return (result);
}

static bool	ft_flood_fill_space(char **map_copy, int row, int col,
	t_cub3d *data)
{
	if (row < 0 || row >= data->map_rows
		|| col < 0 || col >= data->map_cols - 1)
		return (true);
	if (map_copy[row][col] == '1' || map_copy[row][col] == 'V')
		return (true);
	if (map_copy[row][col] == ' ')
	{
		map_copy[row][col] = 'V';
		return (ft_flood_fill_space(map_copy, row - 1, col, data)
			&& ft_flood_fill_space(map_copy, row + 1, col, data)
			&& ft_flood_fill_space(map_copy, row, col - 1, data)
			&& ft_flood_fill_space(map_copy, row, col + 1, data)
			&& ft_flood_fill_space(map_copy, row - 1, col - 1, data)
			&& ft_flood_fill_space(map_copy, row - 1, col + 1, data)
			&& ft_flood_fill_space(map_copy, row + 1, col - 1, data)
			&& ft_flood_fill_space(map_copy, row + 1, col + 1, data));
	}
	return (false);
}

static bool	ft_check_enclosure(char **map_copy, t_cub3d *data)
{
	int		row;
	int		col;
	bool	result;

	row = -1;
	result = true;
	while (++row < data->map_rows)
	{
		col = -1;
		while (++col < data->map_cols)
		{
			if (map_copy[row][col] == '0')
				result = ft_flood_fill_zero(map_copy, row, col, data);
			if (result == false)
				return (false);
		}
	}
	return (result);
}

static bool	ft_flood_fill_zero(char **map_copy, int row, int col,
	t_cub3d *data)
{
	if (row < 0 || row >= data->map_rows
		|| col < 0 || col >= data->map_cols - 1)
		return (false);
	if (map_copy[row][col] == '1' || map_copy[row][col] == 'D'
		|| map_copy[row][col] == 'X')
		return (true);
	if (map_copy[row][col] == '0')
	{
		map_copy[row][col] = 'D';
		return (ft_flood_fill_zero(map_copy, row - 1, col, data)
			&& ft_flood_fill_zero(map_copy, row + 1, col, data)
			&& ft_flood_fill_zero(map_copy, row, col - 1, data)
			&& ft_flood_fill_zero(map_copy, row, col + 1, data)
			&& ft_flood_fill_zero(map_copy, row - 1, col - 1, data)
			&& ft_flood_fill_zero(map_copy, row - 1, col + 1, data)
			&& ft_flood_fill_zero(map_copy, row + 1, col - 1, data)
			&& ft_flood_fill_zero(map_copy, row + 1, col + 1, data));
	}
	return (false);
}
