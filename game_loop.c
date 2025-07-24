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
    
	cast_all_rays(data->player, data);

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

//draw the entire scene based on the pre-calculated wall data
void	draw_frame(t_cub3d *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < PP_WIDTH)
	{
		//draw ceiling for this column
		y = 0;
		while (y < data->wall.top[x])
		{
			ft_pixel_put(&data->image, x, y, 0x87CEEB);
			y++;
		}
		//draw wall for this column
		while (y <= data->wall.bottom[x])
		{
			ft_pixel_put(&data->image, x, y, 0x964B00);
			y++;
		}
		//draw floor for this column
		while (y < PP_HEIGHT)
		{
			ft_pixel_put(&data->image, x, y, 0x556B2F);
			y++;
		}
		x++;
	}
}