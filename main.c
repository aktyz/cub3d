/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:00:34 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/12 10:34:13 by marvin           ###   ########.fr       */
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

		//handle clicking on red cross
		mlx_hook(data->win, 17, 0, close_game, data);

		/*2 - keypress event, when the key is held down its managed by OS as key repeat
		and is stopped when the key is released*/
		//mlx_hook(data->win, 2, 1, handle_keypress, data);
		
		//int	mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);
		mlx_hook(data->win, 2, 1L << 0, handle_keypress, data);     // KeyPress
		mlx_hook(data->win, 3, 1L << 1, handle_keyrelease, data);   // KeyRelease

		
		//add the other keys later
		mlx_loop_hook(data->mlx, game_loop, data);
		mlx_loop(data->mlx);
	
		ft_clean(data);
	}
	return (EXIT_SUCCESS);
}

/*
int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct_ptr)(), void *param);
- win_ptr: the window to apply the hook to
- x_event: the event code (like key press, mouse click, etc.)
- x_mask: the mask that specifies which events to catch (bitmask)
- funct_ptr: the function to call when the event occurs
- param: a parameter passed to the function (your data structure, usually)


17 - event code for DestroyNotify triggered when the user clicks the red close button on the window
0 - a mask that means "just listen to this specific event, no extra filtering needed"

2 - event code for KeyPress
1ll > 0 - boolean expression
1L << 0 (value 1) = KeyPressMask - enables receiving key press events
1L << 1 (value 2) = KeyReleaseMask - enables receiving key release events

*/
