#ifndef A3_4_IULIAGROZA_OFFER_H
#define A3_4_IULIAGROZA_OFFER_H

#include <stdio.h>
#include <stdlib.h>

/*
 * Struct that stores the departure date.
 * */
typedef struct {
    int day;
    int month;
    int year;
} Date;

/*
 * Struct that stores an offer (the main entity).
 * */
typedef struct {
    char *type;
    char *destination;
    Date departureDate;
    double price;
} Offer;

/*
 * Function that creates an Offer object and allocates memory for it and implicitly for its fields.
 * :type: pointer to char (can be "seaside", "mountain", "city break)"
 * :destination: pointer to char
 * :departureDate: Date variable
 * :price: double
 * return: pointer to an Offer object containing type, destination, departureDate, price
 * */
Offer *createOffer(char *type, char *destination, Date departureDate, double price);

/*
 * Function that destroys an Offer object and deallocates its memory and implicitly its fields.
 * :offer: pointer to an Offer object
 * */
void destroyOffer(Offer *offer);

/*
 * Copies an Offer object and returns it.
 * :offer: pointer to an Offer object
 * return: pointer to an Offer object
 * */
Offer *copyOffer(Offer *offer);

/*
 * Getter for the type field of the Offer struct
 * :offer: pointer to an Offer object
 * return: pointer to const char
 * */
const char *getType(Offer *offer);

/*
 * Getter for the destination field of the Offer struct
 * :offer: pointer to an Offer object
 * return: pointer to const char
 * */
const char *getDestination(Offer *offer);

/*
 * Getter for the day of the departureDate field of the Offer struct
 * :offer: pointer to an Offer object
 * return: const int
 * */
const int getDay(Offer *offer);

/*
 * Getter for the month of the departureDate field of the Offer struct
 * :offer: pointer to an Offer object
 * return: const int
 * */
const int getMonth(Offer *offer);

/*
 * Getter for the year of the departureDate field of the Offer struct
 * :offer: pointer to an Offer object
 * return: const int
 * */
const int getYear(Offer *offer);

/*
 * Getter for the price field of the Offer struct
 * :offer: pointer to an Offer object
 * return: double
 * */
double getPrice(Offer *offer);

/*
 * Function that creates a description string containing information about all the fields of an Offer object.
 * */
void toString(Offer *offer);

#endif
