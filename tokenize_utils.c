/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:55:03 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/20 22:20:18 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * If there's any error inside this function, it returns true.
 * Returns false if all good.
 */
bool	ft_new_token(t_cub3d *data, int j, int *i, int k)
{
	t_token	*new_token;

	new_token = ft_calloc(sizeof(t_token), 1);
	if (new_token == NULL)
		return (true);
	new_token->data_id = (t_cub3d_token_types) j;
	if (data->tokens == NULL)
		data->tokens = ft_lstnew((void *) new_token);
	else
		ft_lstadd_back(&data->tokens, ft_lstnew((void *) new_token));
	*i = k + ft_strlen(ft_get_data_identifiers()[j]);
	return (false);
}

bool	ft_new_map_token(t_cub3d *data, int char_count, char *line, int *i)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	new->value = ft_calloc(sizeof(char), char_count + 1);
	if (!new || !new->value)
		return (true);
	ft_strlcpy(new->value, &line[*i], char_count);
	new->data_id = MAP;
	ft_lstadd_back(&data->tokens, ft_lstnew(new));
	data->map_rows++;
	return (false);
}

bool	ft_check_tokens_before_value_add(t_cub3d *data, t_token *last)
{
	if (data->tokens == NULL)
		return (true);
	if ((last->data_id < NO || last->data_id > C)
		|| ((last->data_id >= NO && last->data_id <= C) && last->value != NULL)
		|| (last->data_id && last->value != NULL))
		return (true);
	return (false);
}

void	ft_delete_token(void *token_content_node)
{
	t_token	*content;

	content = (t_token *) token_content_node;
	if (!content)
		return ;
	if (content->value)
	{
		free(content->value);
		content->value = NULL;
	}
	if (content)
	{
		free(content);
		content = NULL;
	}
	token_content_node = NULL;
}

void	ft_parse_cub3d_line(t_cub3d *data, char *line)
{
	int		i;
	int		line_len;
	bool	is_error;

	i = 0;
	line_len = ft_strlen(line);
	is_error = false;
	while (i < line_len)
	{
		is_error = ft_add_token(&i, line, data);
		if (is_error)
		{
			free(line);
			ft_error(TOKENIZING_ERROR, "ft_tokenize", data);
		}
	}
}
