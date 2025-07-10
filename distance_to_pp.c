
#include "cub3d.h"

//convert degrees to raidans (for math functions)
float degrees_to_radians(float degrees) 
{
    return (degrees * (M_PI / 180.0f));
}
/*
the distance between the player and the projection plane at this exact moment


//it calculates the absolute value of an angle of a single ray (if player is looking North, the leftmost ray is 120 degrees)
float get_ray_angle(int column, float player_angle)
{
    float ray_angle;
    float angle_offset_from_center;
    
    //clculate how far the current column is from the center of the screen
    //a negative value means the ray is on the left
    float column_from_center = (float)column - (159.5f);

    //floorf and ceilf because we don't have the real "center ray"
    if (column_from_center < 159.5)
        column_from_center = floorf(column_from_center);
    else
        column_from_center = ceilf(column_from_center);
   
    //calculate the angle offset for this column based on the FOV
    //(the angle between the player's direction and the current ray's direction)
    //it's -30 degrees for the leftmost ray
    angle_offset_from_center = degrees_to_radians(column_from_center * (60 / (float)320));

    //the absolute ray angle is the player's angle plus this offset.
    //for leftmost- 1.0472 radians = 60 degrees
    ray_angle = player_angle - angle_offset_from_center;

    //normalize angle to be between 0 and 2*PI, because it may be problematic to add
    //player's angle and the rey's offset angle and may exceed 360/2PI
    ray_angle = fmod(ray_angle, 2.0f * M_PI);
    if (ray_angle < 0)
    {
        ray_angle += 2.0f * M_PI;
    }
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

