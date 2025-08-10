#include "cub3d.h"


//"up" means in the direction of the increasing y
int is_ray_facing_up(float ray_angle)
{
    if (ray_angle > M_PI && ray_angle < (2.0f * M_PI))
        return (1);
    else
        return (0);
}


int is_ray_horizontal(float ray_angle) 
{
    if (fabsf(sinf(ray_angle)) < EPSILON) 
        return (1);
    return (0);
}

float find_first_horizontal_intersection_y(t_player player, float ray_angle)
{
    //find y-coordinate of the horizontal grid line at or above the player
    float intersection_y;

    if (is_ray_facing_up(ray_angle) == 1)
        intersection_y = floorf(player.player_y / GRID_SIZE) * GRID_SIZE - EPSILON;
    else
        intersection_y = floorf(player.player_y / GRID_SIZE) * GRID_SIZE + GRID_SIZE;

    return (intersection_y);
}


//A.x - first intersection
//based on closest grid y, get the x-value of the point of the intersection
float find_first_horizontal_intersection_x(t_player player, float ray_angle)
{
    first_intersection_y = find_first_horizontal_intersection_y(player, ray_angle);
    //handle horizontal rays ----
    //if (sinf(ray_angle) == 0.0f), , but I try to avoid comparison of float with exact values
    if (is_ray_horizontal(ray_angle))
        return (INFINITY); //it will not cross any next horizontal lines ever
    
    intersection_x = player.player_x + (first_intersection_y - player.player_y) / tanf(ray_angle);

    return (intersection_x);
}
//find the step for y to move each intersection by (in case there's no wall on the current one)
float find_horizontal_step_y(float ray_angle)
{
    if (is_ray_facing_up(ray_angle))
        return (-GRID_SIZE);
    else
        return (GRID_SIZE);
}

//find the step for x to move each intersection by (in case there's no wall on the current one)
float find_horizontal_step_x(float ray_angle)
{
    float y_step;
    float x_step;

    y_step = find_horizontal_step_y(ray_angle);
    x_step = y_step / tanf(ray_angle);

    return (x_step);
}
