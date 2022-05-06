#include "Offer.h"
#include <string.h>

Offer *createOffer(char *type, char *destination, Date departureDate, double price) {
    // Handling NULL/dangling pointers
    if (type == NULL || destination == NULL) {
        return NULL;
    }

    Offer *offer = (Offer *) malloc(sizeof(Offer));
    // Handling NULL/dangling pointers
    if (offer == NULL) {
        return NULL;
    }

    offer->type = malloc(sizeof(char) * (strlen(type) + 1));
    // Handling NULL/dangling pointers
    if (offer->type == NULL) {
        free(offer);
        return NULL;
    }
    strcpy(offer->type, type);

    offer->destination = malloc(sizeof(char) * (strlen(destination) + 1));
    // Handling NULL/dangling pointers
    if (offer->destination == NULL) {
        free(offer->type);
        free(offer);
        return NULL;
    }
    strcpy(offer->destination, destination);

    offer->departureDate = departureDate;
    offer->price = price;

    return offer;
}

void destroyOffer(Offer *offer) {
    // Handling NULL/dangling pointers
    if (offer == NULL) {
        return;
    }

    free(offer->destination);
    free(offer->type);
    free(offer);
}

Offer *copyOffer(Offer *offer) {
    Offer *newOffer = createOffer(offer->type, offer->destination, offer->departureDate, offer->price);
    return newOffer;
}

const char *getType(Offer *offer) {
    // Handling NULL/dangling pointers
    if (offer == NULL) {
        return NULL;
    }

    return offer->type;
}

const char *getDestination(Offer *offer) {
    // Handling NULL/dangling pointers
    if (offer == NULL) {
        return NULL;
    }

    return offer->destination;
}

const int getDay(Offer *offer) {
    // Handling NULL/dangling pointers
    if (offer == NULL) {
        return -1;
    }

    return offer->departureDate.day;
}

const int getMonth(Offer *offer) {
    // Handling NULL/dangling pointers
    if (offer == NULL) {
        return -1;
    }

    return offer->departureDate.month;
}

const int getYear(Offer *offer) {
    // Handling NULL/dangling pointers
    if (offer == NULL) {
        return -1;
    }

    return offer->departureDate.year;
}

double getPrice(Offer *offer) {
    // Handling NULL/dangling pointers
    if (offer == NULL) {
        return -1;
    }

    return offer->price;
}

void toString(Offer *offer) {
    printf("Type: %s; Destination: %s; Departure date: %d/%d/%d; Price: %.2lf\n", offer->type, offer->destination,
           offer->departureDate.day, offer->departureDate.month, offer->departureDate.year, offer->price);
}