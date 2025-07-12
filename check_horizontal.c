#include "cub3d.h"

//i should add a function to check whether a ray is perfectly horiontal, for the loop later

//check which way the ray is facing
//if up - return 1
int is_ray_facing_up(float ray_angle)
{
    if (ray_angle > M_PI && ray_angle < (2.0f * M_PI))
        return (1);
    else
        return (0);
}
//A.y - first intersection
//function with seperate player_y and player_x - below i use the one from the structure t_player instead
/*float find_horizontal_intersection_y(float player_y, int is_ray_facing_up)
{
    //find y-coordinate of the horizontal grid line at or above the player
    int intersection_y;

    if (is_ray_facing_up == 1)
        intersection_y = floorf(player_y / GRID_SIZE) * GRID_SIZE - 1;
    else
        intersection_y = floorf(player_y / GRID_SIZE) * GRID_SIZE + GRID_SIZE;

    return (intersection_y);
}*/


//A.y - first intersection
float find_first_horizontal_intersection_y(t_player player, float ray_angle)
{
    //find y-coordinate of the horizontal grid line at or above the player
    float intersection_y;

    if (is_ray_facing_up(ray_angle) == 1)
        intersection_y = floorf(player.player_y / GRID_SIZE) * GRID_SIZE - 0.0001f;
    else
        intersection_y = floorf(player.player_y / GRID_SIZE) * GRID_SIZE + GRID_SIZE;

    return (intersection_y);
}

//A.x - first intersection
//based on closest grid y, get the x-value of the point of the intersection
float find_first_horizontal_intersection_x(t_player player, float ray_angle)
{
    float first_y_intersection_line; // The Y of the actual grid line
    float intersection_x;

    first_y_intersection_line = find_horizontal_intersection_y(player, ray_angle);

    //handle horizontal rays ----
    //if (sinf(ray_angle) == 0.0f), , but I try to avoid comparison of float with exact values
    if (fabsf(sinf(ray_angle)) < 0.0001f)
        return (INFINITY); //it will not cross any next horizontal lines ever
    
    intersection_x = player.player_x + (first_y_intersection_line - player.player_y) / tanf(ray_angle);

    return (intersection_x);
}

//find the step to move each intersection by (in case there's no wall on the current one)
float find_horizontal_step_y(float ray_angle)
{
    if (is_ray_facing_up(ray_angle) == 1)
        return (GRID_SIZE * (-1));
    else
        return (GRID_SIZE);
}

float find_horizontal_step_x(float ray_angle)
{
    //if (tanf(ray_angle) == 0), but I try to avoid comparison of float with exact values
    if (fabsf(tanf(ray_angle)) < 0.0001f)

        return (INFINITY); //the ray is perfectly horizontal

    //we can't return just GRID_SIZE/tamf(ray_angle) because in the fourth quarter
    //when fay is facing down and to the right, tan is negative, but the step has to move to the right

    //if the ray is facing down
    else if (is_ray_facing_up(ray_angle) == 0)
        return ((-1) * GRID_SIZE / tanf(ray_angle));

    else
        return (GRID_SIZE / tanf(ray_angle));
}
