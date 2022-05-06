#include "Planet.h"
#include <string.h>
#include <stdio.h>

Planet createPlanet(char name[], char type[], double distance)
{
	Planet p;
	strcpy(p.name, name);
	strcpy(p.type, type);
	p.distanceFromEarth = distance;

	return p;
}

char* getName(Planet* p)
{
	return p->name;
}

char* getType(Planet* p)
{
	return p->type;
}

double getDistanceFromEarth(Planet* p)
{
	return p->distanceFromEarth;
}

void toString(Planet p, char str[])
{
	sprintf(str, "Planet %s is a %s planet and its distance from Earth is %.2lf.", p.name, p.type, p.distanceFromEarth);
}