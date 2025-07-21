#include "cub3d.h"

/*We trace 320 rays starting from left to right in a loop
1. Based on the viewing angle, subtract 30 degrees (half of the FOV).
2. Starting from column 0:
-Cast a ray. (The term “cast” is a bit confusing. 
Imagine the player as a wizard who can “cast” rays 
instead of spells. The ray is just an “imaginary” line extending from the player.)
-Trace the ray until it hits a wall.
3. Record the distance to the wall (the distance is equal to the length of the ray).
4. Add the angle increment so that the ray moves to the right (we know from Figure 10 that the value of the angle increment is 60/320 degrees).
5. Repeat step 2 and 3 for each subsequent column until all 320 rays are cast.

In step 2A - we only need to check each grid (instead of pixels)
*/

/*
So, find a point where ray crosses the wall, calculate this distance and write it to an array
*/


//check if the grid at this intersection point - intersection_x and intersection_y
//is a wall. If so - stop and calculate the distance
//map_x_grid, map_y_grid - integer indices of the map grid cell I want to check
//updated values t be passed
// int is_wall_on_grid(int map_x_grid, int map_y_grid, t_game_data *data)
// {
//     //check if the grid's within the map
//     if (map_x_grid < 0 || map_x_grid >= data->map_width_grid ||
//         map_y_grid < 0 || map_y_grid >= data->map_height_grid)
//     {
//         return (1); //outside of the boundaries are treated as a wall to stop rays
//     }

//     //check the map content
//     if (data->map[map_y_grid][map_x_grid] == '1')
//         return (1);

//     return (0); //no wall or it's an empty space character
// }


int is_wall_on_grid(float intersection_x, float intersection_y, t_game_data *data)
{
    int map_x_grid = (int)(intersection_x / GRID_SIZE);
    int map_y_grid = (int)(intersection_y / GRID_SIZE);

    if (map_x_grid < 0 || map_x_grid >= data->map_width_grid ||
        map_y_grid < 0 || map_y_grid >= data->map_height_grid)
        return 1; //out of bounds = treat as wall

    if (data->map[map_y_grid][map_x_grid] == '1')
        return (1); //found a wall

    return (0); //no wall
}

//if there's a wall on the intersection, calculate the distance (both for horizontal and vertical)
//distance = (x2 - xp)/cos(alpha) or (yp - y2)/sin(alpha)
//maybe it would be better to take absolute values? and do something like delta_x and delta_y? for the exact N/S/E/W
float distance_to_the_wall(t_player *player, int column, float intersection_x, float intersection_y)
{
    float distance;
    float ray_angle;

    ray_angle = get_absolute_ray_angle(column, player);

    //exact North
    if (fabsf(ray_angle - (M_PI / 2.0f)) < EPSILON)
        distance = player->player_y - intersection_y;

    //exact South
    else if (fabsf(ray_angle - (3.0f / 2.0f) * M_PI) < EPSILON)
        distance = intersection_y - player->player_y;

    //exact East
    else if (fabsf(ray_angle - 0.0f) < EPSILON)
        distance = intersection_x - player->player_x;
    
    //exact West
    else if (fabsf(ray_angle - M_PI) < EPSILON)
        distance = player->player_x - intersection_x;

    //first quarter
    else if (ray_angle > 0.0f && ray_angle < M_PI / 2.0f)
        distance = (player->player_x - intersection_x) / cosf(ray_angle);
    
    //second quarter
    else if (ray_angle > M_PI / 2.0f && ray_angle < M_PI)
        distance = (player->player_x - intersection_x) / sinf(ray_angle - (M_PI / 2.0f));
    
    //third quarter
    else if (ray_angle > M_PI && ray_angle < (3.0f / 2.0f) * M_PI)
        distance = (player->player_x - intersection_x) / cosf(ray_angle - M_PI);

    //fourth quarter
    else if (ray_angle > (3.0f / 2.0f) * M_PI && ray_angle < 2.0f * M_PI)
        distance = (player->player_x - intersection_x) / sinf(ray_angle - (3.0f / 2.0f) * M_PI);

    return (distance);
}

//a helper function to use in the render_loop
//for now zakladam that the player starts at the very center
void find_wall(t_player player, t_game_data *data, float ray_angle, t_intersection *intersection)
{
    //1. Find first intersection horizontal
    //2. is there a wall?
        // - yes - write it into the intersection structure
        // - no - find new intersection horizontal by adding the horizontal step
    // ...
    // is there a wall? and loop again
    float horizontal_step_x = find_horizontal_step_x(ray_angle);
    float horizontal_step_y = find_horizontal_step_y(ray_angle);

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

float smaller_distance_wall(t_player player, int column, t_intersection *intersection)
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

//function that calculates the correct distances for each ray and keeps them in the
//structure field distances
void cast_all_rays(t_player player, t_game_data *data, t_intersection *intersection)
{
    int column;
    //correct_distance = distorted_distance * cos(beta)
    float correct_distance;
    float distorted_distance;
    float ray_angle;

    
    column = 0;
    while (column < SCREEN_WIDTH)
    {
        ray_angle = get_absolute_ray_angle(column, &player);
        find_wall(player, data, ray_angle, intersection);
        distorted_distance = smaller_distance_wall(player, column, intersection);
        correct_distance = distorted_distance * cosf(get_ray_angle_from_center(column));
        //data->distances[column] = correct_distance;
        data->wall->distances[column] = correct_distance;
        column++;
    }
}

//wall slice will be projected onto the projection plane in next steps

//function to calculate the heights of a wall for each ray
//i cast wall height to an integer because screen space is discrete-
//pixel coordinates are integers
//old version - when wall_height was still in the t_game_data
// void calculate_wall_height(t_game_data *data)
// {
//     //projected_slice_height = (actual_slice_height / distance_to_the_slice) * distance_to_projection_plane;
//     float distance_to_pp = distance_to_projection_plane(); 
//     int i;

//     i = 0;

//     while (i < SCREEN_WIDTH)
//     {
//         //not to divide by 0 when our player is exactly next to the wall
//         if (data->distances[i] != 0)
//             data->wall_height[i] = (int)((GRID_SIZE / data->distances[i]) * distance_to_pp);
//         else
//             data->wall.wall_height[i] = PP_HEIGHT;
//         i++;
//     }
// }

void	calculate_wall_height(t_game_data *data)
{
	int		i; // Represents the current screen column (from 0 to SCREEN_WIDTH-1)
	float	dist_to_wall;
	int		projected_wall_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		//get the distance for the current column from t_game_data.
		dist_to_wall = data->wall->distances[i];

		//screen_height / distance.
		projected_wall_height = (int)(SCREEN_HEIGHT / dist_to_wall);

		data->wall->wall_height[i] = projected_wall_height;

		wall_top_pixel = (SCREEN_HEIGHT / 2) - (projected_wall_height / 2);
		wall_bottom_pixel = (SCREEN_HEIGHT / 2) + (projected_wall_height / 2);

		//ensure the values don't go off-screen
		//important for very close walls that would be "taller" than the screen
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		if (wall_bottom_pixel >= SCREEN_HEIGHT)
			wall_bottom_pixel = SCREEN_HEIGHT - 1;

		//store the final top and bottom values in the t_wall struct
		data->wall->top[i] = wall_top_pixel;
		data->wall->bottom[i] = wall_bottom_pixel;

		i++;
	}
}
//NOT SURE ABOUT THIS IDEA YET
//bottom position of the wall that should be drawn
int bottom_of_wall(t_game_data *data)
{
    while (i < SCREEN_WIDTH)
    {
        SCREEN_HEIGHT - (data->wall_height[i] / 2)
        i++;
    }

}
































//the loop for finding intersection and calculating distance to
//the wall at each column

/*
1. cast a ray
2. trace it until it hits a wall
    a. check horizontal - if there is a wall stop and compare 
        distances to both intersections, choose the closest one
    b. check vertical - if there is a wall stop and compare 
        distances to both intersections, choose the closest one
3. record the distance to the wall
4. add the angle increment and repeat 2 and 3
*/

void render_loop(int column, t_player player, t_game_data data)
{
    float ray_angle;
    int i = 0;

    
    while (i < 319)
    {
        ray_angle = get_ray_angle(i, player); //i or column
        cast_single_ray(data, ray_angle); //cast a single ray

        i++;
    }
}
//check which way the ray is facing
//if up - return 1
int is_facin_up(int column_number)
{
    int facing_up;
    //get the degree
    if (degrees_to_radians(get_angle_from_center(column_number)) > M_PI 
    && degrees_to_radians(get_angle_from_center(column_number)) < 2*M_PI)
        facing_up = 1;
    else
        facing_up = 0;


}

//check if the grid at this intersection point - intersection_x and intersection_y
//is a wall. If so - stop and calculate the distance
int is_wall_on_grid(int map_x_grid, int map_y_grid, t_game_data *data)
{
    //check if the grid's within the map
    if (map_x_grid < 0 || map_x_grid >= data->map_width_grid ||
        map_y_grid < 0 || map_y_grid >= data->map_height_grid)
    {
        return (1); //outside of the boundaries are treated as a wall to stop rays
    }

    //check the map content
    if (data->map[map_y_grid][map_x_grid] == '1')
        return (1);

    return (0); //no wall or it's an empty space character
}

//a helper function to use in the render_loop
void cast_single_ray()

//the loop for finding intersection and calculating distance to
//the wall at each column

void render_loop(int column_number, t_player player)
{
    int i = 0;

    while (i < 319)
    {
        find_horizontal_intersection_y(column_number, player);
        find_horizontal_intersection_x(column_number, player);

    }
}


/*
1. Find ya and xa based on ya
2. check the grid at the intersection point
    if theres a wall - stop and calculate the distance
    if theres NO wall - go to the next intersection point. 
    (new intersection point)
*/


/*my idea (not sure if correct - to discuss)
I look for walls on both horizontal and vertical separately
AND I LOOK FOR THE WALL AS LONG AS I DONT FIND ONE (not sure about this part)
only then I compare the distances and choose the closer intersection
*/

//a function for finding the coordinates of intersections, checking for the wall on the grid
//if there is a wall - return the distance
//if theres NO wall - go to the next intersection point.
//new intersection point: Xnew = Xold + Xa and Ynew = Yold + Ya

//not finished - probably will be placed inside cast_single_ray
float *horizontal_wall(int column, t_player player, float player_angle)
{
    find_horizontal_intersection_y(column, player);
    find_horizontal_intersection_x(column, player);
    is_wall_on_grid(map_x_grind, map_y_grid, data);
    distance_to_the_wall_horizontal(player, horizontal_x, column, player_angle);

}


