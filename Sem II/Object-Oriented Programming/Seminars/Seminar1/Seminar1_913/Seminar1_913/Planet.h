#pragma once

typedef struct
{
	char* name;
	char* type;
	double distanceToEarth;
} Planet;


/// <summary>
/// Creates a planet and returns a pointer to it.
/// </summary>
/// <param name="name">
///		"string" - name for the planet
/// </param>
/// <param name="type">
///		"string"
/// </param>
/// <param name="dist"></param>
/// <returns></returns>
Planet* createPlanet(char* name, char* type, double dist);

/// <summary>
/// Deallocates memory occupied by the Planet.
/// </summary>
/// <param name="p">
///		p - pointer to a Planet
/// </param>
void destroyPlanet(Planet* p);

void testPlanet();

const char* getName(Planet* p);

