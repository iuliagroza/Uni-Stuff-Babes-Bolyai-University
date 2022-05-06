#include "OfferRepo.h"
#include <string.h>

OfferRepo *createRepo() {
    OfferRepo *repo = (OfferRepo *) malloc(sizeof(OfferRepo));
    // Handling NULL/dangling pointers
    if (repo == NULL) {
        return NULL;
    }

    repo->offers = createArray(10);

    return repo;
}

void destroyRepo(OfferRepo *repo) {
    // Handling NULL/dangling pointers
    if (repo == NULL) {
        return;
    }

    destroyArray(repo->offers);
    free(repo);
}

int getSize(OfferRepo *repo) {
    // Handling NULL/dangling pointers
    if (repo == NULL) {
        return -1;
    }

    return getSizeArr(repo->offers);
}

int addRepo(OfferRepo *repo, Offer *offer) {
    // Handling NULL/dangling pointers
    if (repo == NULL || offer == NULL) {
        return 0;
    }

    int position = find(repo->offers, offer);
    if (position == -1) {
        add(repo->offers, offer);
        return 1;
    }
    return 0;
}

Offer *deleteRepo(OfferRepo *repo, char *destination, Date departureDate) {
    // Handling NULL/dangling pointers
    if (repo == NULL || destination == NULL) {
        return NULL;
    }

    Offer *offer = createOffer("seaside", destination, departureDate, 0);

    int position = find(repo->offers, offer);

    destroyOffer(offer);

    if (position != -1) {
        delete(repo->offers, position);
        return repo->offers->elements[position];
    }
    return NULL;
}

Offer *updateRepo(OfferRepo *repo, Offer *offer) {
    // Handling NULL/dangling pointers
    if (repo == NULL || offer == NULL) {
        return NULL;
    }

    int position = find(repo->offers, offer);
    if (position == -1) {
        return NULL;
    }

    update(repo->offers, position, offer);
    return offer;
}