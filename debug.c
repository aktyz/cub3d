/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:27:04 by zslowian          #+#    #+#             */
/*   Updated: 2025/07/09 15:31:21 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_token_list(t_cub3d *data);
void	ft_print_map_player(t_cub3d *data);

void	ft_print_token_list(t_cub3d *data)
{
	t_list	*ptr;
	int		i;
	t_token	*token;

	if (data && data->tokens)
		ptr = data->tokens;
	i = 0;
	while (ptr && ptr->content)
	{
		token = (t_token *) ptr->content;
		ft_printf("token nb: %d\n", i);
		ft_printf("\tdata type:\t%d\n", token->data_id);
		ft_printf("\tdata value:\t%s\n", token->value);
		ptr = ptr->next;
		i++;
	}
}

void	ft_print_map_player(t_cub3d *data)
{
	t_player	*player;
	char		**map;
	int			i;
	char		*ptr;

	player = &data->player;
	map = data->map;
	i = 0;
	if (player->orientation)
	{
		ft_printf("Player information stored in program structure:\n");
		ft_printf("(Position stored as actual 2D array indexes)\n");
		ft_printf("Player row index:\t\t%d\n", player->start_row);
		ft_printf("Player column index:\t\t%d\n", player->start_col);
		ft_printf("Player start orientation:\t%c\n\n", player->orientation);
	}
	if (map)
	{
		ft_printf("Map stored in program data structure:\n\n");
		while (i < data->map_rows)
		{
			ptr = map[i];
			ft_printf("\"");
			while (*ptr < data->map_cols)
			{
				ft_printf("%c", *ptr);
				ptr++;
			}
			ft_printf("\"\n");
			i++;
		}
		ft_printf("\n\n");
	}
}
