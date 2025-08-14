/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:24:41 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/14 15:02:06 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool		ft_is_alphanumeric(char *token);
bool		ft_is_map_valid(t_cub3d *data);
static bool	ft_flood_fill_check(char **map_copy, int row, int col,
				t_cub3d *data);
static char	**ft_copy_map(t_cub3d *data, int map_rows, int map_cols);
static void	ft_free_map_copy(char **map_copy, int map_rows);

/**
 * Function checks if token contains anything else than white spaces.
 * If it contains it - the function returns true and should be added
 * to the token list.
 * Otherwise it contains only whitespace signs and doesn't need to be
 * added.
 *
 */
bool	ft_is_alphanumeric(char *token)
{
	char	*ptr;

	ptr = token;
	while (*ptr)
	{
		if (ft_isalnum(*ptr))
			return (true);
		ptr++;
	}
	return (false);
}

/**
 * Function validating the map provided by the user.
 * It checks if the map is all surounded by walls using
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
	if (!ft_flood_fill_check(map_copy, data->player.start_row,
			data->player.start_col, data))
		is_valid = false;
	ft_free_map_copy(map_copy, data->map_rows);
	return (is_valid);
}

/**
 * Flood fill algorithm to check if all accessible areas are properly enclosed.
 * Returns false if the flood fill reaches the border of the map (invalid map).
 */
static bool	ft_flood_fill_check(char **map_copy, int row, int col,
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
		return (ft_flood_fill_check(map_copy, row - 1, col, data)
			&& ft_flood_fill_check(map_copy, row + 1, col, data)
			&& ft_flood_fill_check(map_copy, row, col - 1, data)
			&& ft_flood_fill_check(map_copy, row, col + 1, data));
	}
	return (false);
}

/**
 * Creates a copy of the map for flood fill validation.
 */
static char	**ft_copy_map(t_cub3d *data, int map_rows, int map_cols)
{
	char	**map_copy;
	int		i;

	map_copy = ft_calloc(map_rows + 1, sizeof(char *));
	if (!map_copy)
		ft_error(MEM_ERROR, "ft_copy_map", data);
	i = 0;
	while (i < map_rows)
	{
		map_copy[i] = ft_calloc(map_cols + 1, sizeof(char));
		if (!map_copy[i])
		{
			ft_free_map_copy(map_copy, i);
			ft_error(MEM_ERROR, "ft_copy_map", data);
		}
		ft_strlcpy(map_copy[i], data->map[i], map_cols + 1);
		i++;
	}
	return (map_copy);
}

/**
 * Frees the map copy used for validation.
 */
static void	ft_free_map_copy(char **map_copy, int map_rows)
{
	int	i;

	if (!map_copy)
		return ;
	i = 0;
	while (i < map_rows)
	{
		if (map_copy[i])
			free(map_copy[i]);
		i++;
	}
	free(map_copy);
}
