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
	float dx;
	float dy;
	float new_x;
	float new_y;

	dx = cosf(data->player.player_angle) * MOVE_SPEED;
	dy = sinf(data->player.player_angle) * MOVE_SPEED;
	new_x = data->player.player_x + dx;
	new_y = data->player.player_y + dy;
	int map_grid_x = (int)(new_x / GRID_SIZE);
	int map_grid_y = (int)(new_y / GRID_SIZE);

	//collision check, update player's position
	if (map_grid_y >= 0 && map_grid_y < data->map_rows &&
		map_grid_x >= 0 && map_grid_x < data->map_cols &&
		data->map[map_grid_y][map_grid_x] != '1')
	{
		data->player.player_x = new_x;
		data->player.player_y = new_y;
	}
}

//moves the player backward by subtracting the forward movement components
void move_backward(t_cub3d *data)
{
	float dx = cosf(data->player.player_angle) * MOVE_SPEED;
	float dy = sinf(data->player.player_angle) * MOVE_SPEED; //assumes y increases downward; no negative sign needed in this coordinate system
	float new_x = data->player.player_x - dx;
	float new_y = data->player.player_y - dy;
	int map_grid_x = (int)(new_x / GRID_SIZE);
	int map_grid_y = (int)(new_y / GRID_SIZE);

	if (map_grid_y >= 0 && map_grid_y < data->map_rows &&
		map_grid_x >= 0 && map_grid_x < data->map_cols &&
		data->map[map_grid_y][map_grid_x] != '1')
	{
		data->player.player_x = new_x;
		data->player.player_y = new_y;
	}
}

//moves the player left
void move_left(t_cub3d *data)
{
	float move_angle = data->player.player_angle - (M_PI / 2.0f);
	float dx = cosf(move_angle) * MOVE_SPEED;
	float dy = sinf(move_angle) * MOVE_SPEED;
	float new_x = data->player.player_x + dx;
	float new_y = data->player.player_y + dy;
	int map_grid_x = (int)(new_x / GRID_SIZE);
	int map_grid_y = (int)(new_y / GRID_SIZE);

	if (map_grid_y >= 0 && map_grid_y < data->map_rows &&
		map_grid_x >= 0 && map_grid_x < data->map_cols &&
		data->map[map_grid_y][map_grid_x] != '1')
	{
		data->player.player_x = new_x;
		data->player.player_y = new_y;
	}
}

void move_right(t_cub3d *data)
{
	float move_angle = data->player.player_angle + (M_PI / 2.0f);
	float dx = cosf(move_angle) * MOVE_SPEED;
	float dy = sinf(move_angle) * MOVE_SPEED;
	float new_x = data->player.player_x + dx;
	float new_y = data->player.player_y + dy;
	int map_grid_x = (int)(new_x / GRID_SIZE);
	int map_grid_y = (int)(new_y / GRID_SIZE);

	if (map_grid_y >= 0 && map_grid_y < data->map_rows &&
		map_grid_x >= 0 && map_grid_x < data->map_cols &&
		data->map[map_grid_y][map_grid_x] != '1')
	{
		data->player.player_x = new_x;
		data->player.player_y = new_y;
	}
}
