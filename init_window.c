#include "cub3d.h"

void window_init(t_projection_plane *projection_plane)
{
    projection_plane->mlx_connection = mlx_init();
    if (projection_plane->mlx_connection == NULL)
        ft_malloc_error();

    projection_plane->mlx_window = mlx_new_window(projection_plane->mlx_connection, WIDTH, HEIGHT, "Cub3d");
    if (projection_plane->mlx_window == NULL)
    {
        mlx_destroy_display(projection_plane->mlx_connection);
        free(projection_plane->mlx_connection);
        ft_malloc_error();
    }
    projection_plane->image.img_ptr = mlx_new_image(projection_plane->mlx_connection, 320, 200);
    if (projection_plane->image.img_ptr == NULL)
    {
		mlx_destroy_window(projection_plane->mlx_connection, projection_plane->mlx_window);
		mlx_destroy_display(projection_plane->mlx_connection);
		free(projection_plane->mlx_connection);
		ft_malloc_error();
    }
    projection_plane->image.pix_ptr = mlx_get_data_addr(projection_plane->image.img_ptr, 
    &projection_plane->image.bpp, &projection_plane->image.line_len, &projection_plane->image.endian);
    
    //init events and data here later:
    // events_init(projection_plane);
    // data_init(projection_plane);
}


// handling failure to allocate mlx structures
void	ft_malloc_error(void)
{
	ft_putstr_fd("Encountered problems with mlx variables initialization\n",
		2);
	exit(EXIT_FAILURE);
}