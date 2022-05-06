#include "Planet.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

Planet *createPlanet(char *name, char *type, double dist) {
    if (name == NULL || type == NULL) {
        return NULL;
    }

    Planet *p = (Planet *) malloc(sizeof(Planet));
    if (p == NULL) {
        return NULL;
    }

    p->name = malloc((strlen(name) + 1) * sizeof(char));
    if (p->name == NULL) {
        free(p);
        return NULL;
    }
    strcpy(planet_name, name);

    p->type = malloc((strlen(type) + 1) * sizeof(char));
    if (p->type == NULL) {
        free(p->name);
        free(p);
        return NULL;
    }

    p->distanceToEarth = dist;
    return p;
}

void destroyPlanet(Planet *p) {
    if (p == NULL) {
        return NULL;
    }

    free(p->name);
    free(p->type);
    free(p);
}

void testPlanet() {
    Planet *p = createPlanet("test name", "test type", 15.2);
    assert(p != NULL);

    destroyPlanet(p);
}

const char *getName(Planet *p) {
    if (p == NULL) {
        return NULL;
    }
    return p->name;
}