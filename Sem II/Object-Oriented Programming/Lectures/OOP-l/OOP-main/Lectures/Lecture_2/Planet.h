#pragma once

typedef struct
{
	char name[50];
	char type[50];
	double distanceFromEarth;
} Planet;

Planet createPlanet(char name[], char type[], double distance);
char* getName(Planet* p);
char* getType(Planet* p);
double getDistanceFromEarth(Planet* p);

void toString(Planet p, char str[]);