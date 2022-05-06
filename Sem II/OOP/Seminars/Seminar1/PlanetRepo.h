#ifndef SEMINAR1_PLANETREPO_H
#define SEMINAR1_PLANETREPO_H

#endif //SEMINAR1_PLANETREPO_H
#include "Planet.h"

typedef struct {
    int size, capacity;
    Planet** data;
} Repo;

Repo* createRepo();

void destroyRepo(Repo* r);

void add(Repo* r, Planet* p);
