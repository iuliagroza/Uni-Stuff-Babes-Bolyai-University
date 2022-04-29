#ifndef SEMINAR1_PLANET_H
#define SEMINAR1_PLANET_H

#endif
//#pragma once // includes everything recursively exactly once in order to respect the One Definition Rule
// works with include guards/macros too (the default for CLion); pragma once might not be standard


typedef struct {
    char *name;
    char *type;
    double distanceToEarth;
} Planet;

/*
* Creates a planet and returns a pointer to it.
*/
Planet *createPlanet(char *name, char *type, double dist);

/*
* Deallocates memory occupied by the Planet.
*/
void destroyPlanet(Planet *p);

/*
*   Tests the creation and destruction of a Planet
*/
void testPlanet();

const char *getName(Planet *p);