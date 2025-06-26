
#include "cub3d.h"

//convert degrees to raidans (for math functions)
float degrees_to_radians(float degrees) 
{
    return (degrees * (M_PI / 180.0f));
}
/*
the distance between the player and the projection plane at this exact moment


/* degrees between the player looking directly in front of them 
and the given column. There are 320 columns total.
 */
//this is the angle from the player's direct line of sight - maybe useful for the future when 
//the pov will be moving? Below a function with absolute wworld angle
// float get_angle_from_center(int column_number) 
// {
//     float angle_per_column;
//     float center_column;
//     int columns_from_center;
//     float angle;

//     center_column = (float)SCREEN_WIDTH / 2.0f;
//     angle_per_column = FOV_DEGREES / (float)SCREEN_WIDTH; //in our case 60/320

//     //number of column steps from the center reference
//     columns_from_center = fabsf(center_column - column_number);

//     angle = angle_per_column * column_offset;
//     return (angle);
// }

float get_ray_angle(int column, float player_angle_rad)
{
    //player_angle_rad is for rotation later - after pressing keys
    float first_ray_angle; //angle of the first ray
    float angle_increment; //increment per 1 columnt
    float ray_angle; //angle for the current column

    first_ray_angle = player_angle_rad - (FOV_RAD / 2.0f);
    angle_increment = FOV_RAD / (float)SCREEN_WIDTH;

    //calculate the angle for the current column
    ray_angle = first_ray_angle + (column * angle_increment);

    //normalize angle to be between 0 and 2*PI, because it may be problematic to add
    //player's angle and the rey's offset angle and may exceed 360/2PI
    ray_angle = fmod(ray_angle, 2.0f * M_PI);
    if (ray_angle < 0)
        ray_angle += 2.0f * M_PI;
    return (ray_angle);
}

//distance to projection plane is fixed
float distance_to_pp(int degree)
{
    float half_fov_degrees;
    float half_fov_radians;
    float half_screen_width;
    float distance;

    half_fov_degrees = FOV_DEGREES / 2.0f;
    half_fov_radians = degrees_to_radians(half_fov_degrees);
    half_screen_width = (float)SCREEN_WIDTH / 2.0f; //160

    //distance to pp = (half_screen_width) / tan(half_FOV_in_radians)
    distance = half_screen_width / tanf(half_fov_radians);
    return (distance); //277.1
}

/*
Check if the wall has been hit by a ray
- I check both vertically and horizontally
- a wall can only be hit on the grid boundary, so we check only those places
- if there is a grid on either of them, the checking stops
*/
/*Render a scene - trace 320 rays starting from left to right, can be done in a loop

*/

float get_angle_from_center(int column_number) 
{
    float angle_per_column;
    float center_column;
    int columns_from_center;
    float angle;

    center_column = (float)SCREEN_WIDTH / 2.0f;
    angle_per_column = FOV_DEGREES / (float)SCREEN_WIDTH; //in our case 60/320

    //number of column steps from the center reference
    columns_from_center = fabsf(center_column - column_number);

    angle = angle_per_column * column_offset;
    return (angle);
}



/*
Check if the wall has been hit by a ray
- I check both vertically and horizontally
- a wall can only be hit on the grid boundary, so we check only those places
- if there is a grid on either of them, the checking stops
*/


/*Render a scene - trace 320 rays starting from left to right, can be done in a loop


*/

