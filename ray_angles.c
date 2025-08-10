
#include "cub3d.h"

//convert degrees to radians (for math functions)
float degrees_to_radians(float degrees) 
{
    return (degrees * (M_PI / 180.0f));
}

//calculates the absolute value of an angle of a single ray (if player is looking North, the leftmost ray is 120 degrees)
float get_absolute_ray_angle(int column, t_player *player)
{
    float ray_angle;
    float angle_from_center;
    
    //calculate how far the current column is from the center of the screen - a negative value means the ray is on the left
    float column_from_center = column - (PP_WIDTH / 2.0f);

   
    /*calculate the angle offset for this column based on the FOV
    (the angle between the player's direction and the current ray's direction), it's -30 degrees for the leftmost ray*/

    angle_from_center = column_from_center * (FOV_RAD / PP_WIDTH);

    //the absolute ray angle is the player's angle plus this offset
    //for leftmost- 1.0472 radians = 60 degrees
    ray_angle = player->player_angle + angle_from_center;

    //normalize angle to be between 0 and 2*PI, because it may be problematic to add
    //player's angle and the rey's offset angle and may exceed 360/2PI
    ray_angle = fmod(ray_angle, 2.0f * M_PI);
    if (ray_angle < 0)
    {
        ray_angle += 2.0f * M_PI;
    }
    return (ray_angle);
}

//calculate the ray angle from the line going directly in front of the player (center) to this specific ray
float get_ray_angle_from_center(int column)
{
    float column_from_center;
    float angle_from_center; 

    column_from_center = (float)column - 159.5f;

    //floor/ceil for non-exact center ray
    if (column_from_center < 0)
        column_from_center = floorf(column_from_center);
    else
        column_from_center = ceilf(column_from_center);
    
    //convert the angle between ray and the center
    angle_from_center = fabs(degrees_to_radians(column_from_center * (FOV / PP_WIDTH)));

    
    return (angle_from_center);
}

//distance to projection plane is fixed
float distance_to_projection_plane(void)
{
    float half_fov_degrees;
    float half_fov_radians;
    float half_screen_width;
    float distance;

    half_fov_degrees = FOV / 2.0f;
    half_fov_radians = degrees_to_radians(half_fov_degrees);
    half_screen_width = (float)PP_WIDTH / 2.0f; //160

    //distance to pp = (half_screen_width) / tan(half_FOV_in_radians)
    distance = half_screen_width / tanf(half_fov_radians);
    return (distance); //277.1
}
