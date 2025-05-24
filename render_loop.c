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

    return (facing_up);
}
//A.y
int find_horizontal_intersection_y(int column_number, t_player player)
{
    //find y-coordinate of the horizontal grid line at or above the player
    int intersection_y;

    if (is_facing_up == 1)
        intersection_y = floor(player.p_y/64) * 64 - 1;
    else
        intersection_y = floor(player.p_y/64) * 64 + 64;

    return (intersection_y);
}

//based on closest grid y, get the x-value of the point of the intersection
int find_horizontal_intersecion_x(int column_number, t_player player)
{
    int point_y = find_horizontal_intersecion_y(column_number, player);
    int intersection_x;
    float alpha = degrees_to_radians(get_angle_from_center(column_number));

    intersection_x = player.p_x + (player.p_y - point_y)/tan(alpha);
    
    return (intersection_x);
}

//check if the grid at this intersection point - intersection_x and intersection_y
//is a wall. If so - stop and calculate the distance


