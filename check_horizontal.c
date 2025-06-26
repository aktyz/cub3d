#include "cub3d.h"

//i should add a function to check whether a ray is perfectly horiontal, for the loop later

//check which way the ray is facing
//if up - return 1
int is_ray_facing_up(float ray_angle_rad)
{
    if (ray_angle_rad > M_PI && ray_angle_rad < (2.0f * M_PI))
        return (1);
    else
        return (0);
}
//A.y
float find_horizontal_intersection_y(float player_y, int is_ray_facing_up)
{
    //find y-coordinate of the horizontal grid line at or above the player
    int intersection_y;

    if (is_ray_facing_up == 1)
        intersection_y = floorf(player_y / GRID_SIZE) * GRID_SIZE - 1; //according to the tutorial - some sources suggest to subtract a smaller value
    else
        intersection_y = floorf(player_y / GRID_SIZE) * GRID_SIZE + GRID_SIZE;

    return (intersection_y);
}
//A.x
//based on closest grid y, get the x-value of the point of the intersection
float find_horizontal_intersection_x(float player_x, float player_y, float ray_angle, int is_ray_facing_up_val)
{
    float first_y_intersection_line; // The Y of the actual grid line
    float intersection_x;

    first_y_intersection_line = find_horizontal_intersection_y(player_y, is_ray_facing_up);

    //handle horizontal rays ----
    if (sinf(ray_angle) == 0.0f)
        return (INFINITY); //it will not cross any next horizontal lines ever
    
    intersection_x = player_x + (first_y_intersection_line - player_y) / tanf(ray_angle);

    return (intersection_x);
}
