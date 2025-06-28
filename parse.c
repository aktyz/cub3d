/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:50:18 by zslowian          #+#    #+#             */
/*   Updated: 2025/06/28 17:56:57 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_parse(t_cub3d *data);
static void	ft_save_info(t_cub3d *data, t_token *token);
static void ft_save_map(t_cub3d *data, t_token *token);
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

	if (data->tokens)
		ptr = data->tokens;
	while (ptr)
	{
		token = (t_token *) ptr->content;
		if (*token->data_id < DATA_ID_NB)
			ft_save_info(data, token);
		else if (*token->data_id == MAP)
			ft_save_map(data, token);
		else
			ft_error(TOKENIZING_ERROR, "ft_parse", data);
		ptr = ptr->next;
	}
}

static void	ft_save_info(t_cub3d *data, t_token *token)
{
	if (0)
	{
		if (*token->data_id == NO)
			ft_strlcpy(data->textures->no_texture, token->value, ft_strlen(token->value));
		else if (*token->data_id == SO)
			ft_strlcpy(data->textures->so_texture, token->value, ft_strlen(token->value));
		else if (*token->data_id == WE)
			ft_strlcpy(data->textures->we_texture, token->value, ft_strlen(token->value));
		else if (*token->data_id == EA)
			ft_strlcpy(data->textures->ea_texture, token->value, ft_strlen(token->value));
		else
			ft_save_color(data, token);
	}
}

static void ft_save_map(t_cub3d *data, t_token *token)
{
	(void) data;
	(void) token;
}

static void ft_save_color(t_cub3d *data, t_token *token)
{
	char	**tmp;
	char	*ptr;

	if (*token->data_id == F)
	{
		tmp = ft_split(token->value, ',');
		ptr = *tmp;
		while (*ptr)
		{
			ft_printf("%s\t", *ptr);
			ptr++;
		}
		ptr = *tmp;
		while (*ptr)
		{
			free(ptr);
			ptr++;
		}
	}
	else if (*token->data_id == C)
	{
		tmp = ft_split(token->value, ',');
		ptr = *tmp;
		while (*ptr)
		{
			ft_printf("%s\t", *ptr);
			ptr++;
		}
	}
	else
		ft_error(ERROR_WHEN_PARSING, "ft_save_info", data);
}