/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:07:54 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/18 20:51:34 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_is_alphanumeric(char *token);
char	**ft_copy_map(t_cub3d *data, int map_rows, int map_cols);
void	ft_free_map_copy(char **map_copy, int map_rows);
void	ft_switch_remaining_zeroes(char **map_copy, t_cub3d *data);

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
 * Creates a copy of the map for flood fill validation.
 */
char	**ft_copy_map(t_cub3d *data, int map_rows, int map_cols)
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
void	ft_free_map_copy(char **map_copy, int map_rows)
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

void	ft_switch_remaining_zeroes(char **map_copy, t_cub3d *data)
{
	int	row;
	int	col;

	row = -1;
	while (++row < data->map_rows)
	{
		col = -1;
		while (++col < data->map_cols - 1)
		{
			if (map_copy[row][col] == '0')
			{
				map_copy[row][col] = '1';
				data->map[row][col] = '1';
			}
		}
	}
}
