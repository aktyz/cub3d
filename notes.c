/*
we needd to now several attributes: 
1. player's height, FOV and player's position
2. Projection plane's dimension
3. Relationhip between player and projection plane

FOV- how wide the pleayer sees the worls in fornt of them (humans 90, not good on screen - 60 better)
player's height - best half the size of walls

POV of the player - x coordinate, y coordinate and the angle the player is facing to

Resolution - 320 units wide, 200 units high (resolution of most VGA video cards) -  1 pixel = 1 unit
one grid - 64x64 units, height = 32


-Dimension of the Projection Plane = 320 x 200 units
-Center of the Projection Plane = (160,100)
-Distance to the Projection Plane = 277 units (calculates after every move i think)
-Angle between subsequent rays = 60/320 degrees

a wall = a collection of 320 wall slices, so instead of tracing a ray for every pixel on the screen,
we can trace only for every vertcal column on the screen

So to render such a sceen, we can simply trace 320 rays starting from left to right (can be in a loop)

HOW TO DO IT:
1. Based on the viewing angle, subtract 30 degrees (half of the FOV).
2. Starting from column 0:
    -Cast a ray. (The term “cast” is a bit confusing. Imagine the player as a wizard who can “cast” rays instead of spells. The ray is just an “imaginary” line extending from the player.)
    -Trace the ray until it hits a wall.
3. Record the distance to the wall (the distance is equal to the length of the ray).
4. Add the angle increment so that the ray moves to the right (we know from Figure 10 that the value of the angle increment is 60/320 degrees).
5. Repeat step 2 and 3 for each subsequent column until all 320 rays are cast.

we dont have to check each pixel, only each grid (the walls can be only on the grid boundary)
BEST: check horizontal and vertical separately. if there is a wall, the checking stops
THEN: the distance to both intersection points is compared, the closer distance is chosen


Steps of finding intersections with HORIZONTAL grid lines:

1. Find coordinate of the first intersection (point A in this example).
2. Find Ya. (Note: Ya is just the height of the grid; however, if the ray is facing up, Ya will be negative, if the ray is facing down, Ya will bepositive.)
3. Find Xa using the equation given above.
4. Check the grid at the intersection point. If there is a wall on the grid, stop and calculate the distance.
5. If there is no wall, extend the to the next intersection point. 
Notice that the coordinate of the next intersection point 
-call it (Xnew,Ynew) is Xnew=Xold+Xa, and Ynew=YOld+Ya.

Steps of finding intersections with VERTICAL grid lines:

Find coordinate of the first intersection (point B in this example).
The ray is facing right in the picture, so B.x = rounded_down(Px/64) * (64) + 64.
If the ray had been facing left B.x = rounded_down(Px/64) * (64) – 1.
A.y = Py + (Px-A.x)*tan(ALPHA);
Find Xa. (Note: Xa is just the width of the grid; however, if the ray is facing right, Xa will be positive, if the ray is facing left, Ya will be negative.)
Find Ya using the equation given above.
Check the grid at the intersection point. If there is a wall on the grid, stop and calculate the distance.
If there is no wall, extend the to the next intersection point. 
Notice that the coordinate of the next intersection point -call it (Xnew,Ynew) is just Xnew=Xold+Xa, and Ynew=YOld+Ya.


Calculate vertcal and horizontal - check which is closer. The wall will be drawn at the closer one.

Two ways of finding distance to the wall:
 - pitagoras
 - trygonometrycznie (cheaper - sinus i cosinus can be calculated beforeahand and put into tables, 
    because Alpha (players POV) has to be between 0 to 360 degrees, number of possibilities are limited )

    The square root way has an unlimited possible values of x and y. 

PROBLEM: fishbowl effect - point farther to the right, not right in front, has a lnger ray
- in real life it works the same, but human eyes are spherical, while the screen is flat.
we must counter this effect.

to remove the viewing distortion, the resulting distance obtained from equations our example
must be multiplied by cos(BETA); where BETA is the angle of the ray that is being cast 
relative to the viewing angle (kąt od ja-sciana (prostopadle) do miejsca, gdzie ray trafil na sciane)
(BETA TO: 30 stopni to the leftmost/rightmost ray). 
When a  person faces the wall "up" it's 90 degrees.


DRAWING WALLS:
the height of the projected wall needs to be found.
Projected Slice Height = (Actual Slice Height/Distance to the Slice) * Distance to Projection Plane

projected slice height = (64 / distance to the slice) * 277

some things can be precomputed - since for example 64/277 will be a const. 
Then a line will be drawn - drawing a vertcal line on the corresponding column on the projection plane (screen)

KONIEC PART 9









*/


