#include "PlanetRepo.h"
#include <stdlib.h>

Repo* createRepo(int capacity)
{
	Repo* r = malloc(sizeof(Repo));
	if (r == NULL)
		return NULL;
	r->size = 0;
	r->capacity = capacity;
	r->data = malloc(sizeof(Planet*) * r->capacity);
	if(r->data == NULL) {
		free(r);
		return NULL;
	}
	return r;
}

void destroyRepo(Repo* r)
{
	if (r == NULL)
		return;
	int i = 0;
	if (r->data == NULL) {
		free(r);
		return;
	}
	for (i = 0; i < r->size; ++i) {
		if (r->data[i] != NULL)
			destroyPlanet(r->data[i]);
	}
	free(r->data);
	free(r);
}
