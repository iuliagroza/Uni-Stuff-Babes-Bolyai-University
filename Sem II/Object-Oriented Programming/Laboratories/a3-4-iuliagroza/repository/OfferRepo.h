#ifndef A3_4_IULIAGROZA_REPOSITORY_H
#define A3_4_IULIAGROZA_REPOSITORY_H

#include "../utils/DynamicArray.h"
#include "../domain/Offer.h"

/*
 * Struct that stores the repo.
 * */
typedef struct {
    DynamicArray *offers;
} OfferRepo;

/*
 * Function that creates an OfferRepo object and allocates memory for it and implicitly for its fields.
 * return: pointer to a OfferRepo object containing the DynamicArray object.
 * */
OfferRepo *createRepo();

/*
 * Function that destroys an OfferRepo object and deallocates its memory and implicitly its fields.
 * :repo: pointer to an OfferRepo object
 * */
void destroyRepo(OfferRepo *repo);

/*
 * Getter for the size field of the OfferRepo struct
 * :repo: pointer to an OfferRepo object
 * return: int
 * */
int getSize(OfferRepo *repo);

/*
 * Function that implements the add functionality using .add() from DynamicArray.h.
 * :repo: pointer to an OfferRepo object
 * :offer: pointer to an Offer object
 * return: int
 * */
int addRepo(OfferRepo *repo, Offer *offer);

/*
 * Function that implements the delete functionality using .delete() from DynamicArray.h.
 * :repo: pointer to an OfferRepo object
 * :destination: pointer to char
 * :departureDate: Date variable
 * return: pointer to Offer object
 * */
Offer *deleteRepo(OfferRepo *repo, char *destination, Date departureDate);

/*
 * Function that implements the update functionality using .update() from DynamicArray.h.
 * :repo: pointer to an OfferRepo object
 * :offer: pointer to an Offer object
 * return: pointer to Offer object
 * */
Offer *updateRepo(OfferRepo *repo, Offer *offer);

#endif
