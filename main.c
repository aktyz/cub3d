/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:00:34 by zslowian          #+#    #+#             */
/*   Updated: 2025/07/25 18:55:22 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_cub3d	*data;

	if (argc != 2)
		ft_error(MAIN_ARGS, "main", NULL);
	
	else
	{
		data = ft_calloc(sizeof(t_cub3d), 1);
		if (data == NULL)
			ft_error(MEM_ERROR, "main", data);
		ft_init(argv[1], data);
		setup_player_and_map(data);
	
		//initialize mlx
		init_mlx(data);

		//KONIEC NOWE
		mlx_hook(data->win, 17, 0, close_game, data);
		mlx_hook(data->win, 2, 1ll > 0, handle_keypress, data); //dolozone //inne
		
		//add the other keys later
		mlx_loop_hook(data->mlx, game_loop, data);
		mlx_loop(data->mlx);
	
		ft_clean(data);
	}
	return (EXIT_SUCCESS);
}