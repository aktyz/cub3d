#include "cub3d.h"

int is_wall_on_grid(float intersection_x, float intersection_y, t_cub3d *data)
{
    int map_x_grid = (int)(intersection_x / GRID_SIZE);
    int map_y_grid = (int)(intersection_y / GRID_SIZE);

    if (map_x_grid < 0 || map_x_grid >= data->map_cols ||
        map_y_grid < 0 || map_y_grid >= data->map_rows)
        return 1; //out of bounds = treat as wall

    if (data->map[map_y_grid][map_x_grid] == '1')
        return (1); //found a wall

    return (0); //no wall
}

//calculate the distance to the wall for a specific ray
float distance_to_the_wall(t_player *player, int column, float intersection_x, float intersection_y)
{
    float distance;
    float ray_angle;

    float delta_y = intersection_y - player->player_y;
    float delta_x = intersection_x - player->player_x;

    ray_angle = get_absolute_ray_angle(column, player);

    //exact North
    if (fabsf((float)(ray_angle - (M_PI / 2.0f))) < EPSILON)
        distance = fabsf(delta_y);

    //exact South
    else if (fabsf((float)(ray_angle - (3.0f / 2.0f) * M_PI)) < EPSILON)
        distance = fabsf(delta_y);

    //exact East
    else if (fabsf(ray_angle - 0.0f) < EPSILON)
        distance = fabsf(delta_x);
    
    //exact West
    else if (fabsf((float)(ray_angle - M_PI)) < EPSILON)
        distance = fabsf(delta_x);

    //first quarter
    else if (ray_angle > 0.0f && ray_angle < M_PI / 2.0f)
        distance = fabsf((delta_x) / cosf(ray_angle));
    
    //second quarter
    else if (ray_angle > M_PI / 2.0f && ray_angle < M_PI)
        distance = fabsf((delta_x) / sinf(ray_angle - (M_PI / 2.0f)));
    
    //third quarter
    else if (ray_angle > M_PI && ray_angle < (3.0f / 2.0f) * M_PI)
        distance = fabsf((delta_x) / cosf(ray_angle - M_PI));

    //fourth quarter
    else if (ray_angle > (3.0f / 2.0f) * M_PI && ray_angle < 2.0f * M_PI)
        distance = fabsf((delta_x) / sinf(ray_angle - (3.0f / 2.0f) * M_PI));

    return (distance);
}

void find_wall(t_player *player, t_cub3d *data, float ray_angle, t_intersection *intersection)
{
    //1. Find first intersection horizontal
    //2. is there a wall?
        // - yes - write it into the intersection structure
        // - no - find new intersection horizontal by adding the horizontal step
    // ...
    // is there a wall? and loop again
    float horizontal_step_x = find_horizontal_step_x(ray_angle);
    float horizontal_step_y = find_horizontal_step_y(ray_angle);

    // printf("Ray angle: %f, Steps: (x=%f, y=%f)\n", 
    //        ray_angle, horizontal_step_x, horizontal_step_y); //debug printf

    float vertical_step_x = find_vertical_step_x(ray_angle);
    float vertical_step_y = find_vertical_step_y(ray_angle);

    //horizontal
    intersection->intersection_hor_y = find_first_horizontal_intersection_y(player, ray_angle);
    intersection->intersection_hor_x = find_first_horizontal_intersection_x(player, ray_angle);
    while (is_wall_on_grid(intersection->intersection_hor_x, intersection->intersection_hor_y, data) != 1)
    {
        intersection->intersection_hor_y += horizontal_step_y;
        intersection->intersection_hor_x += horizontal_step_x;
    }

    //vertical
    intersection->intersection_ver_y = find_first_vertical_intersection_y(player, ray_angle);
    intersection->intersection_ver_x = find_first_vertical_intersection_x(player, ray_angle);
    while (is_wall_on_grid(intersection->intersection_ver_x, intersection->intersection_ver_y, data) != 1)
    {
        intersection->intersection_ver_y += vertical_step_y;
        intersection->intersection_ver_x += vertical_step_x;
    }
}

float find_and_set_wall_data(t_cub3d *data, int column, float ray_angle, t_intersection *intersection)
{
    float distance_hor;
    float distance_ver;

    //calculate distances to both horizontal and vertical intersections
    distance_hor = distance_to_the_wall(&data->player, column, intersection->intersection_hor_x, intersection->intersection_hor_y);
    distance_ver = distance_to_the_wall(&data->player, column, intersection->intersection_ver_x, intersection->intersection_ver_y);

    if (distance_hor <= distance_ver)
    {
        //the ray hit a horiontal wall
        data->wall.wall_hit[column] = intersection->intersection_hor_x;
        
        //determine if it's a N or S wall based on ray direction
        //a ray facing up (towards increasing Y) hits the bottom of a wall, which is a S
        if (is_ray_facing_up(ray_angle))
            data->wall.wall_face[column] = SO;
        else //a ray facing down hits the top of a wall, a N
            data->wall.wall_face[column] = NO;
            
        return (distance_hor);
    }
    else
    {
        //the ray hit a vertical wall
        data->wall.wall_hit[column] = intersection->intersection_ver_y;

        //determine if it's an E or W wall based on ray direction
        //a ray facing right hits the left side of a wall, a W face
        if (is_ray_facing_right(ray_angle))
             data->wall.wall_face[column] = WE;
        else //a ray facing left hits the right side of a wall, an E
             data->wall.wall_face[column] = EA;

        return (distance_ver);
    }
}

//calculate where wall was hit first (the closer intersection)
float smaller_distance_wall(t_player *player, int column, t_intersection *intersection)
{
    float distance_hor;
    float distance_ver;

    distance_hor = distance_to_the_wall(player, column, intersection->intersection_hor_x, intersection->intersection_hor_y);
    distance_ver = distance_to_the_wall(player, column, intersection->intersection_ver_x, intersection->intersection_ver_y);

    if (distance_hor <= distance_ver)
        return (distance_hor);
    else
        return (distance_ver);
}

//calculate the correct distances for each ray 
void cast_all_rays(t_player *player, t_cub3d *data)
{
    int             column;
    float           correct_distance;
    float           distorted_distance;
    float           ray_angle;
    t_intersection  intersection;
    
    column = 0;
    while (column < PP_WIDTH)
    {
        ray_angle = get_absolute_ray_angle(column, player);
        //printf("Column: %d, Ray Angle: %f\n", column, ray_angle); //debug
        find_wall(player, data, ray_angle, &intersection);
        distorted_distance = smaller_distance_wall(player, column, &intersection);
        
        //find the coordinates of the wall hit
        find_wall(player, data, ray_angle, &intersection);
        
        //calculate distance andset the wall face and hit place
        distorted_distance = find_and_set_wall_data(data, column, ray_angle, &intersection);
        
        //correct for fish-bowl
        correct_distance = distorted_distance * cosf(get_ray_angle_from_center(column));

        data->wall.distances[column] = correct_distance;
        column++;
    }
}

//calculate the projected wall height based on the actual wall height and distance to it
void	calculate_wall_height(t_cub3d *data)
{
	int		column; // represents the current screen column (from 0 to PP_WIDTH-1)
	float	dist_to_wall;
	int		projected_wall_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;

	column = 0;
	while (column < PP_WIDTH)
	{
		//get the distance for the current column
		dist_to_wall = data->wall.distances[column];

        //projected wall height = (actual slice height / distance to the slice ) * distance to the projection plane
		projected_wall_height = (int)((GRID_SIZE / dist_to_wall) * distance_to_projection_plane()); //moje
        //projected_wall_height = (int)((GRID_SIZE / dist_to_wall) * 277.1f); //proba  projection plane
        //printf("Column: %d, Projected Wall Height: %d\n", column, projected_wall_height); //debug printf
		data->wall.wall_height[column] = projected_wall_height;

		wall_top_pixel = (PP_HEIGHT / 2) - (projected_wall_height / 2);
		wall_bottom_pixel = (PP_HEIGHT / 2) + (projected_wall_height / 2);

		//ensure the values don't go off-screen- important for very close walls that would be "taller" than the screen
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		if (wall_bottom_pixel >= PP_HEIGHT)
			wall_bottom_pixel = PP_HEIGHT - 1;

		//store the final top and bottom values in the t_wall struct
		data->wall.top[column] = wall_top_pixel;
		data->wall.bottom[column] = wall_bottom_pixel;

		column++;
	}
}
