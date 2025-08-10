#include "cub3d.h"

int is_ray_facing_right(float ray_angle)
{
    //right: 0 to PI/2 (exclusive) OR 3PI/2 (exclusive) to 2PI
    if ((ray_angle >= 0 && ray_angle < (M_PI / 2.0f)) ||
        (ray_angle > (3.0f * M_PI / 2.0f) && ray_angle < (2.0f * M_PI)))
        return (1);
    //edge case of exactly 0 or 2PI
    if (fabsf(ray_angle) < 0.00001f || fabsf((float)(ray_angle - 2.0f * M_PI)) < 0.00001f) 
        return (1);
    return (0);
}


//check for vertical rays (cos(angle) is 0) - angle PI/2 or 3PI/2
int is_ray_vertical(float ray_angle) 
{
    if (fabsf(cosf(ray_angle)) < 0.00001f) 
        return (1);
    return (0);
}

float find_first_vertical_intersection_x(t_player player, float ray_angle)
{
    float first_intersection_x;

    if (is_ray_facing_right(ray_angle) == 0) // Facing left
        first_intersection_x = floorf(player.player_x / GRID_SIZE) * GRID_SIZE - EPSILON;
    else // Facing right
        first_intersection_x = floorf(player.player_x / GRID_SIZE) * GRID_SIZE + GRID_SIZE;

    return (first_intersection_x);
}

float find_first_vertical_intersection_y(t_player player, float ray_angle)
{
    float first_intersection_y;
    float first_intersection_x = find_first_vertical_intersection_x(player, ray_angle);

    //vertical rays (cos(angle) == 0 for PI/2 or 3PI/2 radians)
    //A perfectly vertical ray will not cross any other of the vertical lines
    if (is_ray_vertical(ray_angle))
        return (INFINITY);

    first_intersection_y = player.player_y + (first_intersection_x - player.player_x) * tanf(ray_angle);

    return (first_intersection_y);
}

//find the step for x to move each intersection by (in case there's no wall on the current one)
float find_vertical_step_x(float ray_angle)
{
    if (is_ray_facing_right(ray_angle) == 1)
        return (GRID_SIZE);
    else
        return ((-1) * GRID_SIZE);
}


//find the step for y to move each intersection by (in case there's no wall on the current one)
float find_vertical_step_y(float ray_angle)
{
    float x_step;

    x_step = find_vertical_step_x(ray_angle);

    //if the ray is perfectly vertical tan is undefined, but x_step is 0 - this check handles it
    if (is_ray_vertical(ray_angle))
    {
        if (is_ray_facing_up(ray_angle))
            return (-GRID_SIZE); //if facing up, step is negative
        else
            return (GRID_SIZE);  //if facing down, step is positive
    }
    else
    {
        x_step = find_vertical_step_x(ray_angle);
        return (x_step * tanf(ray_angle));
    }
}
