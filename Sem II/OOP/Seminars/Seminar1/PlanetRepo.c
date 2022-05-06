#include "PlanetRepo.h"
#include <stdlib.h>

Repo *createRepo() {
    Repo *r = malloc(sizeof(Repo));
    if (r == NULL) {
        return NULL;
    }

    r->size = 0;

    r->capacity = 10;

    r->data = malloc(sizeof(Planet *) * r->capacity);
    if (r->data == NULL) {
        free(r);
        return NULL;
    }

    return r;
}

void destroyRepo(Repo *r) {
    if(r == NULL) {
        return;
    }

    if(r->data == NULL) {
        free(r);
        return;
    }

    for(int i = 0; i < r->size; i++) {
        if(r->data[i] != NULL) {
            destroyPlanet(r->data[i]);
        }
    }

    free(r->data);
}

void add(Repo *r, Planet *p) {

}