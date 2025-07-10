#include "cub3d.h"

int is_ray_facing_right(float ray_angle)
{
    //right: 0 to PI/2 (exclusive) OR 3PI/2 (exclusive) to 2PI
    if ((ray_angle >= 0 && ray_angle < (M_PI / 2.0f)) ||
        (ray_angle > (3.0f * M_PI / 2.0f) && ray_angle < (2.0f * M_PI)))
        return (1);
    //edge case of exactly 0 or 2PI
    if (fabsf(ray_angle) < 0.00001f || fabsf(ray_angle - 2.0f * M_PI) < 0.00001f) 
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

float find_vertical_intersection_x(t_player player, float ray_angle)
{
    float intersection_x;

    if (is_ray_facing_right(ray_angle) == 1)
    {
        //if facing right - the first vertical line is to the right of the player's current grid cell
        intersection_x = floorf(player.player_x / GRID_SIZE) * GRID_SIZE + GRID_SIZE;
    }
    //else - if it's facing left
    else
        intersection_x = floorf(player.player_x / GRID_SIZE) * GRID_SIZE - 0.0001f; //left edge of the players current grid, the -1 puts the point inside the grid cell

    return (intersection_x);
}

float find_vertical_intersection_y(t_player player, float ray_angle, float first_x_intersection_line)
{
    float intersection_y;

    //vertical rays (cos(angle) == 0 for PI/2 or 3PI/2 radians)
    //ay perfectly vertical ray will not cross any other of the vertical lines
    if (is_ray_vertical(ray_angle))
        return (INFINITY);

    intersection_y = player.player_y + (first_x_intersection_line - player.player_x) * tanf(ray_angle);

    return (intersection_y);
}

//find the step to move each intersection by (in case there's no wall on the current one)
float find_vertical_step_x(float ray_angle)
{
    if (is_ray_facing_right(ray_angle) == 1)
        return (GRID_SIZE);
    else
        return ((-1) * GRID_SIZE);
}

float find_vertical_step_y(float ray_angle)
{
    if (is_ray_facing_right(ray_angle) == 1)
        return ((-1) * GRID_SIZE * tanf(ray_angle));
    else
        return (GRID_SIZE * tanf(ray_angle));
}

float look_for_wall_on_vertical(t_player player, float ray_angle, float first_x_intersection_line)
{
    //where to take first_x_intersection_line from?
    float first_vertical_x = find_vertical_intersection_x(player, ray_angle);
    float first_vertical_y = find_vertical_intersection_y(player, ray_angle, first_x_intersection_line);

    is_wall_on_grid(int map_x_grid, int map_y_grid, t_game_data *data)
}