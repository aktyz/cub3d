#include "cub3d.h"

int is_ray_facing_right(float ray_angle_rad)
{
    //right: 0 to PI/2 (exclusive) OR 3PI/2 (exclusive) to 2PI
    if ((ray_angle_rad >= 0 && ray_angle_rad < (M_PI / 2.0f)) ||
        (ray_angle_rad > (3.0f * M_PI / 2.0f) && ray_angle_rad < (2.0f * M_PI)))
    {
        return (1);
    }
    //edge case of exactly 0 or 2PI
    if (fabsf(ray_angle_rad) < 0.00001f || fabsf(ray_angle_rad - 2.0f * M_PI) < 0.00001f) 
    {
        return (1);
    }
    return (0);
}


//check for vertical rays (cos(angle) is 0) - angle PI/2 or 3PI/2
int is_ray_vertical(float ray_angle_rad) 
{
    if (fabsf(cosf(ray_angle_rad)) < 0.00001f) 
        return (1);
    return (0);
}

float find_vertical_intersection_x(float player_x, int is_ray_facing_right)
{
    float intersection_x;

    if (is_ray_facing_right == 1)
    {
        //if facing right - the first vertical line is to the right of the player's current grid cell
        intersection_x = floorf(player_x / GRID_SIZE) * GRID_SIZE + GRID_SIZE;
    }
    //else - if it's facing left
    else
        intersection_x = floorf(player_x / GRID_SIZE) * GRID_SIZE - 1; //or without -1?

    return (intersection_x);
}

float find_vertical_intersection_y(float player_x, float player_y, float first_x_intersection_line, float ray_angle_rad)
{
    float intersection_y;

    //vertical rays (cos(angle) == 0 for PI/2 or 3PI/2 radians)
    //ay perfectly vertical ray will not cross any other of the vertical lines
    if (is_ray_vertical(ray_angle_rad))
        return (INFINITY);

    intersection_y = player_y + (first_x_intersection_line - player_x) * tanf(ray_angle_rad);

    return (intersection_y);
}