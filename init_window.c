#include "cub3d.h"


void init_mlx(t_cub3d *data)
{
	data->mlx = mlx_init();
    if (!data->mlx)
        ft_error(MEM_ERROR, "init_mlx", data);
        
    //create the window with bigger, scaled dimensions
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
    if (!data->win)
        ft_error(MEM_ERROR, "init_mlx", data);
        
    //create the image buffer with small, rendering dimensions
	data->image.img_ptr = mlx_new_image(data->mlx, PP_WIDTH, PP_HEIGHT);
    if (!data->image.img_ptr)
    {

        ft_error(MEM_ERROR, "init_mlx", data);
    }

	data->image.pix_ptr = mlx_get_data_addr(data->image.img_ptr, &data->image.bpp,
			&data->image.line_len, &data->image.endian);
}

//get pixel color from the smaller image
unsigned int get_pixel_color(t_img *image, int x, int y)
{
	char *pixel_address;

	pixel_address = image->pix_ptr + (y * image->line_len + x * (image->bpp / 8));
	return (*(unsigned int *)pixel_address);
}

void render_scaled_frame(t_cub3d *data)
{
    int src_x;
    int src_y;
    int dest_x;
    int dest_y;
    int color;

    src_y = 0;
    while (src_y < PP_HEIGHT)
    {
        src_x = 0;
        while (src_x < PP_WIDTH)
        {
            //gGet the color of one pixel from small image
            color = get_pixel_color(&data->image, src_x, src_y);

            //draw a larger block of this colour onto the bigger window
            dest_y = src_y * SCALE;
            while (dest_y < (src_y * SCALE) + SCALE)
            {
                dest_x = src_x * SCALE;
                while (dest_x < (src_x * SCALE) + SCALE)
                {
                    mlx_pixel_put(data->mlx, data->win, dest_x, dest_y, color);
                    dest_x++;
                }
                dest_y++;
            }
            src_x++;
        }
        src_y++;
    }
}