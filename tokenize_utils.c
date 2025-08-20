/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:55:03 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/20 15:07:01 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_new_token(t_cub3d *data, int j, int *i, int k)
{
	t_token	*new_token;

	new_token = ft_calloc(sizeof(t_token), 1);
	if (new_token == NULL)
		ft_error(MEM_ERROR, "ft_new_token", data);
	new_token->data_id = (t_cub3d_token_types) j;
	if (data->tokens == NULL)
		data->tokens = ft_lstnew((void *) new_token);
	else
		ft_lstadd_back(&data->tokens, ft_lstnew((void *) new_token));
	*i = k + ft_strlen(ft_get_data_identifiers()[j]);
}

void	ft_check_tokens_before_value_add(t_cub3d *data, t_token *last)
{
	if (data->tokens == NULL)
		ft_error(TOKENIZING_ERROR, "ft_add_data_id_value", data);
	if ((last->data_id < NO || last->data_id > C)
		|| ((last->data_id >= NO && last->data_id <= C) && last->value != NULL)
		|| (last->data_id && last->value != NULL))
		ft_error(TOKENIZING_ERROR,
			"ft_add_data_id_value - data value is being added on wrong token",
			data);
}
