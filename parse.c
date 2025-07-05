/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:50:18 by zslowian          #+#    #+#             */
/*   Updated: 2025/07/05 14:16:49 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_parse(t_cub3d *data);
static void	ft_save_info(t_cub3d *data, t_token *token);
static void ft_save_map(t_cub3d *data, t_list **ptr);
static void ft_save_color(t_cub3d *data, t_token *token);

/**
 * Function transforming token list into validated program data:
 * - it translates data tokens into the global data information
 * - it creates an array representing the map of the level
 *
 */
void	ft_parse(t_cub3d *data)
{
	t_list	*ptr;
	t_token	*token;

	if (data->map_rows < 3)
		ft_error(WRONG_MAP, "ft_parse - map has to little rows", data);
	if (data->tokens)
		ptr = data->tokens;
	while (ptr)
	{
		token = (t_token *) ptr->content;
		if (token->data_id < DATA_ID_NB)
			ft_save_info(data, token);
		else if (token->data_id == MAP)
			ft_save_map(data, &ptr);
		else
			ft_error(TOKENIZING_ERROR, "ft_parse", data);
		if (ptr && ptr->next)
			ptr = ptr->next;
	}
}

static void	ft_save_info(t_cub3d *data, t_token *token)
{
	if (data->textures == NULL)
		data->textures = ft_calloc(1, sizeof(t_file_names));
	if (data->textures == NULL)
		ft_error(MEM_ERROR, "ft_save_info - textures", data);
	if (token->data_id == NO)
	{
		data->textures->no_texture = ft_calloc(ft_strlen(token->value) + 1, sizeof(char));
		if (!data->textures->no_texture)
			ft_error(MEM_ERROR, "ft_save_info - no_texture", data);
		ft_strlcpy(data->textures->no_texture, token->value, ft_strlen(token->value) + 1);
	}
	else if (token->data_id == SO)
	{
		data->textures->so_texture = ft_calloc(ft_strlen(token->value) + 1, sizeof(char));
		if (!data->textures->so_texture)
			ft_error(MEM_ERROR, "ft_save_info - so_texture", data);
		ft_strlcpy(data->textures->so_texture, token->value, ft_strlen(token->value) + 1);
	}
	else if (token->data_id == WE)
	{
		data->textures->we_texture = ft_calloc(ft_strlen(token->value) + 1, sizeof(char));
		if (!data->textures->we_texture)
			ft_error(MEM_ERROR, "ft_save_info - we_texture", data);
		ft_strlcpy(data->textures->we_texture, token->value, ft_strlen(token->value) + 1);
	}
	else if (token->data_id == EA)
	{
		data->textures->ea_texture = ft_calloc(ft_strlen(token->value) + 1, sizeof(char));
		if (!data->textures->ea_texture)
			ft_error(MEM_ERROR, "ft_save_info - ea_texture", data);
		ft_strlcpy(data->textures->ea_texture, token->value, ft_strlen(token->value) + 1);
	}
	else
		ft_save_color(data, token);
}

/**
 * When parsing the map tokens into the 2D array this function validates
 * as well:
 * - that map tokens are uninterrupted by different types tokens (iterate through ptr)
 * - that map contains only allowed characters
 * - that map lines are all of the same length (map_length)
 * - that the map DO contains the player position with correct value
 */
static void ft_save_map(t_cub3d *data, t_list **ptr)
{
	int		map_length;
	t_token	*map_token;
	int		map_tokens_nb;

	map_token = (t_token *) (*ptr)->content;
	map_length = ft_strlen(map_token->value);
	if (map_length < 3)
		ft_error(WRONG_MAP, "ft_save_map - map has too little columns", data);
	data->map = ft_calloc(data->map_rows + 1, sizeof(char*));
	if (!data->map)
		ft_error(MEM_ERROR, "ft_save_map", data);
	map_tokens_nb = 0;
	while (ptr && *ptr) // for each MAP token
	{
		if (!ft_validate_map_line_len(&map_length, map_token))
			ft_error(WRONG_MAP, "ft_save_map - wrong row length", data);
		ft_copy_map_token_to_struct(map_token->value, &map_tokens_nb, data);
		if ((*ptr)->next) // check if there's a next token that it is also of MAP type
		{
			map_token = (t_token *) (*ptr)->next->content;
			if (map_token->data_id != MAP)
				ft_error(WRONG_MAP, "ft_save_map - map token list interrupted", data);
		}
		*ptr = (*ptr)->next;
	}
	if (!data->player.orientation)
		ft_error(WRONG_MAP, "ft_save_map - player pos missing", data);
}

static void ft_save_color(t_cub3d *data, t_token *token)
{
	char	**color_values;

	if (data->colors == NULL)
		data->colors = ft_calloc(1, sizeof(t_colors));
	if (data->colors == NULL)
		ft_error(MEM_ERROR, "ft_save_color", data);
	color_values = ft_split(token->value, ',');
	if (token->data_id == F)
		ft_store_rgb(data->colors->floor_color, color_values);
	else if (token->data_id == C)
		ft_store_rgb(data->colors->ceiling_color, color_values);
	else
		ft_error(ERROR_WHEN_PARSING, "ft_save_info", data);
}
