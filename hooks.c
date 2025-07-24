#include "cub3d.h"

int	close_game(t_cub3d *data)
{
	ft_clean(data);
	exit(EXIT_SUCCESS);
	return (0);
}

int	handle_keypress(int keycode, t_cub3d *data)
{

	if (keycode == XK_Escape)
		close_game(data);
	//other keys will be added here in the future
	return (0);
}