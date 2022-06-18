#pragma once

#include "Planet.h"

typedef struct {
	int size, capacity;
	Planet** data;
} Repo;

Repo* createRepo();
void destroyRepo(Repo* r);
void addToRepo(Repo* r, Planet* p);