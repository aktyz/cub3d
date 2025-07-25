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

	//look left
	if (keycode == XK_Left)
		look_left(data);
	
	if (keycode == XK_Right)
		look_right(data);

	//other keys will be added here in the future
	return (0);
}

//for now the view will change by PI/2 with the key pressed once
void look_left(t_cub3d *data)
{
	//this means change player_angle from the current to the player_angle + PI/2
	float player_angle;

	player_angle = data->player.player_angle;

	//case for when the player is facing S
	if (player_angle == ((3.0f / 2.0f) * M_PI))
		player_angle = 0.0f;

	else
		player_angle += M_PI / 2.0f;

	data->player.player_angle = player_angle;
}

void look_right(t_cub3d *data)
{
	float player_angle;

	player_angle = data->player.player_angle;
	
	//case for when the player is facing N
	if (player_angle == (M_PI / 2.0f))
		player_angle = 0.0f;

	else
		player_angle -= M_PI / 2.0f;

	data->player.player_angle = player_angle;
}

/*movement - WASD keys
move as long as the key is still held down
OR as long as the player doesn't "hit" the wall

What if 2 keys are pressed at the same time? will the system "choose"one?


*/