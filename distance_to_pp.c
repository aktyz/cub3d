
/*
the distance between the player and the projection plane at this exact moment

-Dimension of the Projection Plane = 320 x 200 units
-Angle between subsequent rays = 60/320 degrees
*/

#include "math.h"

/* degrees between the player looking directly in front of them 
and the given column. There are 320 columns total.
 */
int get_degrees(int column_number)
{
    //angle between subsequent columns/rays = 60/320
    //column 0
    int degree;

    degree = 60/320 * (abs(160 - column_number));
    return (degree);   
}

//distance to projection plane at this exact moment
//it is calculated based on the degree at which this exact column is viewed at
int get_distance_to_pp(int degree)
{
    int distance_to_pp;
    distance_to_pp = 160/tan(degree);

    return (distance_to_pp);
}