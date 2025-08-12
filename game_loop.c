#include "cub3d.h"

void setup_player_and_map(t_cub3d *data)
{
	//set player coordinates from the parsed start_row/col - the player is placed in the middle of the grid (+ 0.5)
	data->player.player_x = (data->player.start_col + 0.5) * GRID_SIZE;
	data->player.player_y = (data->player.start_row + 0.5) * GRID_SIZE;


	//set starting angle based on 'N', 'S', 'E', 'W'
	if (data->player.orientation == 'E') data->player.player_angle = 0;
	if (data->player.orientation == 'S') data->player.player_angle = M_PI / 2.0;
	if (data->player.orientation == 'W') data->player.player_angle = M_PI;
	if (data->player.orientation == 'N') data->player.player_angle = 3.0 * M_PI / 2.0;

	//replace the player character on the map with floor
	data->map[data->player.start_row][data->player.start_col] = '0';
}

int game_loop(t_cub3d *data)
{
    //player movement logic will be here
	if (data->input.move_right)
        move_right(data);
    if (data->input.move_left)
        move_left(data);
    if (data->input.move_forward)
        move_forward(data);
    if (data->input.move_backward)
        move_backward(data);
    if (data->input.turn_left)
	{

        look_left(data);
	}
    if (data->input.turn_right)
	{
        look_right(data);

	}
    
	cast_all_rays(&data->player, data);

    //calculate wall heights, tops, bottoms
    calculate_wall_height(data);
    
    //draw the screen (ceiling, walls, floor)
    draw_frame(data);

    //image to the window
	render_scaled_frame(data);
    return (0);
}

//it will be changed for textures in the future
void	ft_pixel_put(t_img *image, int x, int y, int color)
{
	char	*pxl;

	pxl = image->pix_ptr + (y * image->line_len + x * (image->bpp / 8));
	*(unsigned int *)pxl = color;
}

/*draws a single vertical slice of a textured wall for a given column
 * It calculates the correct texture coordinates (texture_x, texture_y)
 * for each pixel of the wall slice and draws it to the image buffer
 */
static void	draw_wall_slice(t_cub3d *data, int x)
{
	t_texture_data	*texture;
	int				y;
	int				texture_x;
	int				texture_y;
	int				dist_from_top;

	//determine which texture to use (NO, SO, WE, EA)
	texture = &data->textures_data[data->wall.wall_face[x]];

	//calculate texture_x: the vertical stripe of the texture to use
	texture_x = (int)((fmod(data->wall.wall_hit[x], GRID_SIZE)
				/ GRID_SIZE) * texture->width);

	//flip the texture for opposite-facing walls to prevent a mirrored look
	if (data->wall.wall_face[x] == SO || data->wall.wall_face[x] == WE)
		texture_x = texture->width - 1 - texture_x;

	//loop through each vertical pixel of the wall slice on the screen
	y = data->wall.top[x];
	while (y < data->wall.bottom[x])
	{
		//calculate texture_y: the horizontal pixel of the texture to use
		dist_from_top = y + (data->wall.wall_height[x] / 2) - (PP_HEIGHT / 2);
		texture_y = (int)(((double)dist_from_top / data->wall.wall_height[x])
				* texture->height);

		//get the color from the texture and draw the pixel to our image.
		ft_pixel_put(&data->image, x, y,
			get_texture_pixel_color(texture, texture_x, texture_y));
		y++;
	}
}

/*Draws a complete frame (ceiling, walls, and floor) to the image buffer
 * It iterates through every column of the projection plane
 */
void	draw_frame(t_cub3d *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < PP_WIDTH)
	{
		//draw the ceiling for this column from the top to the wall's top
		y = 0;
		while (y < data->wall.top[x])
		{
			ft_pixel_put(&data->image, x, y, 0x87CEEB); //ceiling color
			y++;
		}

		//draw the textured wall for this column
		draw_wall_slice(data, x);

		//draw the floor from the wall's bottom to the screen's bottom
		y = data->wall.bottom[x];
		while (y < PP_HEIGHT)
		{
			ft_pixel_put(&data->image, x, y, 0x556B2F); //floor color
			y++;
		}
		x++;
	}
}