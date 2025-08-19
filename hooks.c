#include "cub3d.h"

int	close_game(t_cub3d *data)
{
	ft_clean(data);
	exit(EXIT_SUCCESS);
	return (0);
}


int	handle_keypress(int keycode, t_cub3d *data)
{

	//printf("Key pressed: %d\n", keycode); //debug printf

	if (keycode == XK_Escape)
		close_game(data);

	if (keycode == XK_Left)
		data->input.turn_left = true;
	else if (keycode == XK_Right)
		data->input.turn_right = true;
	else if (keycode == KEY_D)
		data->input.move_right = true;
	else if (keycode == KEY_A)
		data->input.move_left = true;
	else if (keycode == KEY_W)
		data->input.move_forward = true;
	else if (keycode == KEY_S)
		data->input.move_backward = true;
	return (0);
}


int	handle_keyrelease(int keycode, t_cub3d *data)
{
	if (keycode == XK_Left)
		data->input.turn_left = false;
	else if (keycode == XK_Right)
		data->input.turn_right = false;
	else if (keycode == KEY_D)
		data->input.move_right = false;
	else if (keycode == KEY_A)
		data->input.move_left = false;
	else if (keycode == KEY_W)
		data->input.move_forward = false;
	else if (keycode == KEY_S)
		data->input.move_backward = false;
	return (0);
}

void look_right(t_cub3d *data)
{
	data->player.player_angle += ROTATION_SPEED;
	//wrap the angle to keep it in the range [0, 2 * PI)
	if (data->player.player_angle >= 2.0f * M_PI)
		data->player.player_angle -= 2.0f * M_PI;
}

void look_left(t_cub3d *data)
{
	data->player.player_angle -= ROTATION_SPEED;
	//wrap the angle to keep it in the range [0, 2 * PI)
	if (data->player.player_angle < 0)
		data->player.player_angle += 2.0f * M_PI;
}

void move_forward(t_cub3d *data)
{
	float 				dx;
	float 				dy;
	t_float_position	new;
	t_int_position		map_grid;

	dx = cosf(data->player.player_angle) * MOVE_SPEED;
	dy = sinf(data->player.player_angle) * MOVE_SPEED;
	new.x = data->player.player_x + dx;
	new.y = data->player.player_y + dy;
	map_grid.x = (int)(new.x / GRID_SIZE);
	map_grid.y = (int)(new.y / GRID_SIZE);
	ft_update_player_pos(data, map_grid, new);
}

//moves the player backward by subtracting the forward movement components
void move_backward(t_cub3d *data)
{
	float 				dx;
	float 				dy;
	t_float_position	new;
	t_int_position		map_grid;

	dx = cosf(data->player.player_angle) * MOVE_SPEED;
	dy = sinf(data->player.player_angle) * MOVE_SPEED; //assumes y increases downward; no negative sign needed in this coordinate system
	new.x = data->player.player_x - dx;
	new.y = data->player.player_y - dy;
	map_grid.x = (int)(new.x / GRID_SIZE);
	map_grid.y = (int)(new.y / GRID_SIZE);
	ft_update_player_pos(data, map_grid, new);
}

//moves the player left
void move_left(t_cub3d *data)
{
	float 				dx;
	float 				dy;
	t_float_position	new;
	t_int_position		map_grid;

	float move_angle = data->player.player_angle - (M_PI / 2.0f);
	dx = cosf(move_angle) * MOVE_SPEED;
	dy = sinf(move_angle) * MOVE_SPEED;
	new.x = data->player.player_x + dx;
	new.y = data->player.player_y + dy;
	map_grid.x = (int)(new.x / GRID_SIZE);
	map_grid.y = (int)(new.y / GRID_SIZE);
	ft_update_player_pos(data, map_grid, new);
}

void move_right(t_cub3d *data)
{
	float 				dx;
	float 				dy;
	t_float_position	new;
	t_int_position		map_grid;

	float move_angle = data->player.player_angle + (M_PI / 2.0f);
	dx = cosf(move_angle) * MOVE_SPEED;
	dy = sinf(move_angle) * MOVE_SPEED;
	new.x = data->player.player_x + dx;
	new.y = data->player.player_y + dy;
	map_grid.x = (int)(new.x / GRID_SIZE);
	map_grid.y = (int)(new.y / GRID_SIZE);
	ft_update_player_pos(data, map_grid, new);
}
