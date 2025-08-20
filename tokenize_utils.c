/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:55:03 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/20 14:57:57 by zslowian         ###   ########.fr       */
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
