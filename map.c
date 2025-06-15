/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:42:30 by zslowian          #+#    #+#             */
/*   Updated: 2025/06/15 18:50:42 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_add_map_line(int *i, char *line, t_cub3d *data);

void	ft_add_map_line(int *i, char *line, t_cub3d *data)
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
	new = ft_calloc(sizeof(t_token), 1);
	new->value = ft_calloc(sizeof(char), char_count + 1);
	ft_strlcpy(new->value, &line[*i], char_count);
	new->data_id = "MAP";
	ft_lstadd_back(&data->tokens, ft_lstnew(new));
	*i += char_count;
}
