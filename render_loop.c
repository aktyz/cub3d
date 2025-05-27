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

//Find a place where the ray hits the wall - horizontal grid lines

//find coordinate of the first intersection (A)
//grid coordinates are integers







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
