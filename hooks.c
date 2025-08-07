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
	// Wrap the angle to keep it in the range [0, 2 * PI)
	if (data->player.player_angle >= 2.0f * M_PI)
		data->player.player_angle -= 2.0f * M_PI;
}

void look_left(t_cub3d *data)
{
	data->player.player_angle -= ROTATION_SPEED;
	// Wrap the angle to keep it in the range [0, 2 * PI)
	if (data->player.player_angle < 0)
		data->player.player_angle += 2.0f * M_PI;
}
void move_forward(t_cub3d *data)
{
	float dx = cosf(data->player.player_angle) * MOVE_SPEED;
	float dy = sinf(data->player.player_angle) * MOVE_SPEED;
	float new_x = data->player.player_x + dx;
	float new_y = data->player.player_y + dy;
	int map_grid_x = (int)(new_x / GRID_SIZE);
	int map_grid_y = (int)(new_y / GRID_SIZE);

	// collision check, update player's position
	if (data->map[map_grid_y][map_grid_x] != '1')
	{
		data->player.player_x = new_x;
		data->player.player_y = new_y;
	}
}

//moves the player backward by subtracting the forward movement components
void move_backward(t_cub3d *data)
{
	float dx = cosf(data->player.player_angle) * MOVE_SPEED;
	float dy = sinf(data->player.player_angle) * MOVE_SPEED; // Correct: NO negative sign
	float new_x = data->player.player_x - dx;
	float new_y = data->player.player_y - dy;
	int map_grid_x = (int)(new_x / GRID_SIZE);
	int map_grid_y = (int)(new_y / GRID_SIZE);

	if (data->map[map_grid_y][map_grid_x] != '1')
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

	if (data->map[map_grid_y][map_grid_x] != '1')
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

	if (data->map[map_grid_y][map_grid_x] != '1')
	{
		data->player.player_x = new_x;
		data->player.player_y = new_y;
	}
}

// //stare
// void look_right(t_cub3d *data)
// {
// 	float player_angle;

// 	player_angle = data->player.player_angle;
	
// 	//case for when the player is facing N
// 	if (player_angle == (M_PI / 80.0f))
// 		player_angle = 0.0f;

// 	else
// 		player_angle += M_PI / 80.0f;

// 	data->player.player_angle = player_angle;
// }

//stare
// void look_left(t_cub3d *data)
// {
// 	//this means change player_angle from the current to the player_angle + PI/2
// 	float player_angle;

// 	player_angle = data->player.player_angle;

// 	//case for when the player is facing S
// 	if (player_angle == ((79.0f / 80.0f) * M_PI))
// 		player_angle = 0.0f;

// 	else
// 		player_angle -= M_PI / 80.0f;

// 	data->player.player_angle = player_angle;
// }






























// //moje poniej
// void move_right(t_cub3d *data)
// {
//     float   move_angle;
//     float   new_x;//for now the view will change by PI/2 with the key pressed once
//     float   new_y;

// 	//direction in which the player will move
//     move_angle = data->player.player_angle - (M_PI / 2.0f);

//     move_angle = fmod(move_angle, 2.0f * M_PI);
//     if (move_angle < 0)
//         move_angle += 2.0f * M_PI;

//     //first quarter
// 	if (data->player.player_angle >= 0 && data->player.player_angle < M_PI / 2.0f)
// 	{
// 		new_x = data->player.player_x + fabsf(cosf(move_angle) * MOVE_SPEED);
//     	new_y = data->player.player_y + fabsf(sinf(move_angle) * MOVE_SPEED);
// 	}

// 	//second quarter
// 	else if (data->player.player_angle >= M_PI / 2.0f && data->player.player_angle < M_PI)
// 	{
// 		new_x = data->player.player_x + fabsf(cosf(move_angle) * MOVE_SPEED);
// 		new_y = data->player.player_y - fabsf(sinf(move_angle) * MOVE_SPEED);
// 	}

// 	//third quarter
// 	else if (data->player.player_angle >= M_PI && data->player.player_angle < (3.0f * M_PI / 2.0f))
// 	{
// 		new_x = data->player.player_x - fabsf(cosf(move_angle) * MOVE_SPEED);
// 		new_y = data->player.player_y - fabsf(sinf(move_angle) * MOVE_SPEED);
// 	}

// 	//fourth quarter
// 	else if (data->player.player_angle >= (3.0f * M_PI / 2.0f))
// 	{
// 		new_x = data->player.player_x - fabsf(cosf(move_angle) * MOVE_SPEED);
// 		new_y = data->player.player_y + fabsf(sinf(move_angle) * MOVE_SPEED);
// 	}

	



	
// 	// //fourth quarter -> first
// 	// else if (data->player.player_angle >= 0 && data->player.player_angle < M_PI / 2.0f)
// 	// {
// 	// 	new_x = data->player.player_x - fabsf(cosf(move_angle) * MOVE_SPEED);
// 	// 	new_y = data->player.player_y + fabsf(sinf(move_angle) * MOVE_SPEED);
// 	// }

// 	// //third quarter -> second
// 	// else if (data->player.player_angle >= M_PI / 2.0f && data->player.player_angle < M_PI)
// 	// {
// 	// 	new_x = data->player.player_x - fabsf(cosf(move_angle) * MOVE_SPEED);
// 	// 	new_y = data->player.player_y - fabsf(sinf(move_angle) * MOVE_SPEED);
// 	// }

// 	// //second quarter -> thirf
// 	// else if (data->player.player_angle >= M_PI && data->player.player_angle < (3.0f * M_PI / 2.0f))
// 	// {
// 	// 	new_x = data->player.player_x + fabsf(cosf(move_angle) * MOVE_SPEED);
// 	// 	new_y = data->player.player_y - fabsf(sinf(move_angle) * MOVE_SPEED);
// 	// }

// 	// //first quarter -> fourth
// 	// if (data->player.player_angle >= (3.0f * M_PI / 2.0f))
// 	// {
// 	// 	new_x = data->player.player_x + fabsf(cosf(move_angle) * MOVE_SPEED);
//     // 	new_y = data->player.player_y + fabsf(sinf(move_angle) * MOVE_SPEED);
// 	// }




// 	//collision detection
//     int map_grid_x = (int)(new_x / GRID_SIZE);
//     int map_grid_y = (int)(new_y / GRID_SIZE);
    
// 	//map boundaries
//     if (map_grid_y >= 0 && map_grid_y < data->map_rows &&
//         map_grid_x >= 0 && map_grid_x < data->map_cols &&
//         data->map[map_grid_y][map_grid_x] != '1')
//     {
//         data->player.player_x = new_x;
//         data->player.player_y = new_y;
//     }
// }
// void move_left(t_cub3d *data)
// {
// 	float move_angle;
// 	float new_x;
// 	float new_y;
	
	
// 	move_angle = data->player.player_angle + (M_PI / 2.0f);
	
// 	move_angle = fmod(move_angle, 2.0f * M_PI);
//     if (move_angle > M_PI * 2.0f)
// 	{
//         move_angle -= 2.0f * M_PI;
// 	}
	
// 	//first quarter
// 	if (data->player.player_angle >= 0 && data->player.player_angle < M_PI / 2.0f)
// 	{
// 		new_x = data->player.player_x - fabsf(cosf(move_angle) * MOVE_SPEED);
//     	new_y = data->player.player_y - fabsf(sinf(move_angle) * MOVE_SPEED);
// 	}

// 	//second quarter
// 	else if (data->player.player_angle >= M_PI / 2.0f && data->player.player_angle < M_PI)
// 	{
// 		new_x = data->player.player_x - fabsf(cosf(move_angle) * MOVE_SPEED);
// 		new_y = data->player.player_y + fabsf(sinf(move_angle) * MOVE_SPEED);
// 	}

// 	//third quarter
// 	else if (data->player.player_angle >= M_PI && data->player.player_angle < (3.0f * M_PI / 2.0f))
// 	{
// 		new_x = data->player.player_x + fabsf(cosf(move_angle) * MOVE_SPEED);
// 		new_y = data->player.player_y + fabsf(sinf(move_angle) * MOVE_SPEED);
// 	}

// 	//fourth quarter
// 	else if (data->player.player_angle >= (3.0f * M_PI / 2.0f))
// 	{
// 		new_x = data->player.player_x + fabsf(cosf(move_angle) * MOVE_SPEED);
// 		new_y = data->player.player_y - fabsf(sinf(move_angle) * MOVE_SPEED);
// 	}

// 	//collision detection
//     int map_grid_x = (int)(new_x / GRID_SIZE);
//     int map_grid_y = (int)(new_y / GRID_SIZE);
    
// 	//map boundaries
//     if (map_grid_y >= 0 && map_grid_y < data->map_rows &&
//         map_grid_x >= 0 && map_grid_x < data->map_cols &&
//         data->map[map_grid_y][map_grid_x] != '1')
//     {
//         data->player.player_x = new_x;
//         data->player.player_y = new_y;
//     }

// }


// //new idea - doesnt work still
// void move_forward(t_cub3d *data)
// {
// 	float dx = cosf(data->player.player_angle) * MOVE_SPEED;
// 	float dy = -sinf(data->player.player_angle) * MOVE_SPEED;

// 	float new_x = data->player.player_x + dx;
// 	float new_y = data->player.player_y + dy;

//     int map_grid_x = (int)(new_x / GRID_SIZE);
//     int map_grid_y = (int)(new_y / GRID_SIZE);
    
//     if (map_grid_y >= 0 && map_grid_y < data->map_rows &&
//         map_grid_x >= 0 && map_grid_x < data->map_cols &&
//         data->map[map_grid_y][map_grid_x] != '1')
//     {
//         data->player.player_x = new_x;
//         data->player.player_y = new_y;
//     }
// }

// void move_backward(t_cub3d *data)
// {
// 	float dx = -cosf(data->player.player_angle) * MOVE_SPEED;
// 	float dy = sinf(data->player.player_angle) * MOVE_SPEED;

// 	float new_x = data->player.player_x + dx;
// 	float new_y = data->player.player_y + dy;

//     int map_grid_x = (int)(new_x / GRID_SIZE);
//     int map_grid_y = (int)(new_y / GRID_SIZE);
    
//     if (map_grid_y >= 0 && map_grid_y < data->map_rows &&
//         map_grid_x >= 0 && map_grid_x < data->map_cols &&
//         data->map[map_grid_y][map_grid_x] != '1')
//     {
//         data->player.player_x = new_x;
//         data->player.player_y = new_y;
//     }
// }

//jakies starse
// void move_forward(t_cub3d *data)
// {
// 	float move_angle;
// 	float new_x;
// 	float new_y;

// 	move_angle = data->player.player_angle;

//     //first quarter
// 	if (data->player.player_angle >= 0 && data->player.player_angle < M_PI / 2.0f)
// 	{
// 		new_x = data->player.player_x + fabsf(cosf(move_angle) * MOVE_SPEED);
//     	new_y = data->player.player_y - fabsf(sinf(move_angle) * MOVE_SPEED);
// 	}

// 	//second quarter
// 	else if (data->player.player_angle >= M_PI / 2.0f && data->player.player_angle < M_PI)
// 	{
// 		new_x = data->player.player_x - fabsf(cosf(move_angle) * MOVE_SPEED);
// 		new_y = data->player.player_y - fabsf(sinf(move_angle) * MOVE_SPEED);
// 	}

// 	//third quarter
// 	else if (data->player.player_angle >= M_PI && data->player.player_angle < (3.0f * M_PI / 2.0f))
// 	{
// 		new_x = data->player.player_x - fabsf(cosf(move_angle) * MOVE_SPEED);
// 		new_y = data->player.player_y + fabsf(sinf(move_angle) * MOVE_SPEED);
// 	}

// 	//fourth quarter
// 	else if (data->player.player_angle >= (3.0f * M_PI / 2.0f))
// 	{
// 		new_x = data->player.player_x + fabsf(cosf(move_angle) * MOVE_SPEED);
// 		new_y = data->player.player_y + fabsf(sinf(move_angle) * MOVE_SPEED);
// 	}

// 	//collision detection
//     int map_grid_x = (int)(new_x / GRID_SIZE);
//     int map_grid_y = (int)(new_y / GRID_SIZE);
    
// 	//map boundaries
//     if (map_grid_y >= 0 && map_grid_y < data->map_rows &&
//         map_grid_x >= 0 && map_grid_x < data->map_cols &&
//         data->map[map_grid_y][map_grid_x] != '1')
//     {
//         data->player.player_x = new_x;
//         data->player.player_y = new_y;
//     }
// }

// void move_backward(t_cub3d *data)
// {
// 	float move_angle;
// 	float new_x;
// 	float new_y;

// 	move_angle = data->player.player_angle;

//     //first quarter
// 	if (data->player.player_angle >= 0 && data->player.player_angle < M_PI / 2.0f)
// 	{
// 		new_x = data->player.player_x - fabsf(cosf(move_angle) * MOVE_SPEED);
//     	new_y = data->player.player_y + fabsf(sinf(move_angle) * MOVE_SPEED);
// 	}

// 	//second quarter
// 	else if (data->player.player_angle >= M_PI / 2.0f && data->player.player_angle < M_PI)
// 	{
// 		new_x = data->player.player_x + fabsf(cosf(move_angle) * MOVE_SPEED);
// 		new_y = data->player.player_y + fabsf(sinf(move_angle) * MOVE_SPEED);
// 	}

// 	//third quarter
// 	else if (data->player.player_angle >= M_PI && data->player.player_angle < (3.0f * M_PI / 2.0f))
// 	{
// 		new_x = data->player.player_x + fabsf(cosf(move_angle) * MOVE_SPEED);
// 		new_y = data->player.player_y - fabsf(sinf(move_angle) * MOVE_SPEED);
// 	}

// 	//fourth quarter
// 	else if (data->player.player_angle >= (3.0f * M_PI / 2.0f))
// 	{
// 		new_x = data->player.player_x - fabsf(cosf(move_angle) * MOVE_SPEED);
// 		new_y = data->player.player_y - fabsf(sinf(move_angle) * MOVE_SPEED);
// 	}

// 	//collision detection
//     int map_grid_x = (int)(new_x / GRID_SIZE);
//     int map_grid_y = (int)(new_y / GRID_SIZE);
    
// 	//map boundaries
//     if (map_grid_y >= 0 && map_grid_y < data->map_rows &&
//         map_grid_x >= 0 && map_grid_x < data->map_cols &&
//         data->map[map_grid_y][map_grid_x] != '1')
//     {
//         data->player.player_x = new_x;
//         data->player.player_y = new_y;
//     }
// }
