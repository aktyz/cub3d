#include "cub3d.h"

int	close_game(t_cub3d *data)
{
	ft_clean(data);
	exit(EXIT_SUCCESS);
	return (0);
}
// //moje
// int	handle_keypress(int keycode, t_cub3d *data)
// {

// 	if (keycode == XK_Escape)
// 		close_game(data);

// 	//look left
// 	if (keycode == XK_Left)
// 		look_left(data);
	
// 	if (keycode == XK_Right)
// 		look_right(data);
	
// 	if (keycode == XK_D)
// 		move_right(data);

// 	//other keys will be added here in the future
// 	return (0);
// }

int	handle_keypress(int keycode, t_cub3d *data)
{

	//printf("Key pressed: %d\n", keycode); //debug printf

	if (keycode == XK_Escape)
		close_game(data);

	if (keycode == XK_Left)
		data->input.turn_left = true;
	else if (keycode == XK_Right)
		data->input.turn_right = true;
	else if (keycode == 100)
		data->input.move_right = true;
	else if (keycode == 97)
		data->input.move_left = true;
	else if (keycode == 119)
		data->input.move_forward = true;
	else if (keycode == 115)
		data->input.move_backward = true;
	return (0);
}


int	handle_keyrelease(int keycode, t_cub3d *data)
{
	if (keycode == XK_Left)
		data->input.turn_left = false;
	else if (keycode == XK_Right)
		data->input.turn_right = false;
	else if (keycode == 100)
		data->input.move_right = false;
	else if (keycode == 97)
		data->input.move_left = false;
	else if (keycode == 119)
		data->input.move_forward = false;
	else if (keycode == 115)
		data->input.move_backward = false;
	return (0);
}



//for now the view will change by PI/2 with the key pressed once
void look_left(t_cub3d *data)
{
	//this means change player_angle from the current to the player_angle + PI/2
	float player_angle;

	player_angle = data->player.player_angle;

	//case for when the player is facing S
	if (player_angle == ((49.0f / 50.0f) * M_PI))
		player_angle = 0.0f;

	else
		player_angle += M_PI / 50.0f;

	data->player.player_angle = player_angle;
}

void look_right(t_cub3d *data)
{
	float player_angle;

	player_angle = data->player.player_angle;
	
	//case for when the player is facing N
	if (player_angle == (M_PI / 50.0f))
		player_angle = 0.0f;

	else
		player_angle -= M_PI / 50.0f;

	data->player.player_angle = player_angle;
}

/*movement - WASD keys
move as long as the key is still held down
OR as long as the player doesn't "hit" the wall

*/


void move_right(t_cub3d *data)
{
    float   move_angle;
    float   new_x;
    float   new_y;

	//direction in which the player will move
    move_angle = data->player.player_angle - (M_PI / 2.0f);

    move_angle = fmod(move_angle, 2.0f * M_PI);
    if (move_angle < 0)
        move_angle -= 2.0f * M_PI;

    new_x = data->player.player_x + cosf(move_angle) * MOVE_SPEED;
    new_y = data->player.player_y + sinf(move_angle) * MOVE_SPEED;

	//collision detection
    int map_grid_x = (int)(new_x / GRID_SIZE);
    int map_grid_y = (int)(new_y / GRID_SIZE);
    
	//map boundaries
    if (map_grid_y >= 0 && map_grid_y < data->map_rows &&
        map_grid_x >= 0 && map_grid_x < data->map_cols &&
        data->map[map_grid_y][map_grid_x] != '1')
    {
        data->player.player_x = new_x;
        data->player.player_y = new_y;
    }
}


void move_left(t_cub3d *data)
{
	float move_angle;
	float new_x;
	float new_y;

	move_angle = data->player.player_angle - (M_PI / 2.0f);

	move_angle = fmod(move_angle, 2.0f * M_PI);
    if (move_angle < 0)
        move_angle -= 2.0f * M_PI;

    new_x = data->player.player_x - cosf(move_angle) * MOVE_SPEED;
    new_y = data->player.player_y - sinf(move_angle) * MOVE_SPEED;

	//collision detection
    int map_grid_x = (int)(new_x / GRID_SIZE);
    int map_grid_y = (int)(new_y / GRID_SIZE);
    
	//map boundaries
    if (map_grid_y >= 0 && map_grid_y < data->map_rows &&
        map_grid_x >= 0 && map_grid_x < data->map_cols &&
        data->map[map_grid_y][map_grid_x] != '1')
    {
        data->player.player_x = new_x;
        data->player.player_y = new_y;
    }

}

void move_forward(t_cub3d *data)
{
	float move_angle;
	float new_x;
	float new_y;

	move_angle = data->player.player_angle;

	move_angle = fmod(move_angle, 2.0f * M_PI);
    if (move_angle < 0)
        move_angle -= 2.0f * M_PI;

    new_x = data->player.player_x + cosf(move_angle) * MOVE_SPEED;
    new_y = data->player.player_y - sinf(move_angle) * MOVE_SPEED;

	//collision detection
    int map_grid_x = (int)(new_x / GRID_SIZE);
    int map_grid_y = (int)(new_y / GRID_SIZE);
    
	//map boundaries
    if (map_grid_y >= 0 && map_grid_y < data->map_rows &&
        map_grid_x >= 0 && map_grid_x < data->map_cols &&
        data->map[map_grid_y][map_grid_x] != '1')
    {
        data->player.player_x = new_x;
        data->player.player_y = new_y;
    }
}


void move_backward(t_cub3d *data)
{
	float move_angle;
	float new_x;
	float new_y;

	move_angle = data->player.player_angle;

	move_angle = fmod(move_angle, 2.0f * M_PI);
    if (move_angle < 0)
        move_angle -= 2.0f * M_PI;

    new_x = data->player.player_x - cosf(move_angle) * MOVE_SPEED;
    new_y = data->player.player_y + sinf(move_angle) * MOVE_SPEED;

	//collision detection
    int map_grid_x = (int)(new_x / GRID_SIZE);
    int map_grid_y = (int)(new_y / GRID_SIZE);
    
	//map boundaries
    if (map_grid_y >= 0 && map_grid_y < data->map_rows &&
        map_grid_x >= 0 && map_grid_x < data->map_cols &&
        data->map[map_grid_y][map_grid_x] != '1')
    {
        data->player.player_x = new_x;
        data->player.player_y = new_y;
    }
}