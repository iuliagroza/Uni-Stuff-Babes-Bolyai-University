#ifndef A3_4_IULIAGROZA_CONTROLLER_H
#define A3_4_IULIAGROZA_CONTROLLER_H

#include "../repository/OfferRepo.h"
#include "../undoredo/command.h"

/*
 * Struct that stores information about the controller.
 * */
typedef struct {
    OfferRepo *repo;
    OperationStack *undoStack;
    OperationStack *redoStack;
} Controller;

/*
 * Function that creates a Controller object and allocates memory for it and implicitly for its fields.
 * :repo: pointer to OfferRepo object
 * return: pointer to a Controller object containing the repo (OfferRepo) object.
 * */
Controller *createController(OfferRepo *repo, OperationStack *undoStack, OperationStack *redoStack);

/*
 * Function that destroys a Controller and deallocates its memory and implicitly its fields.
 * :ctrl: pointer to a Controller object
 * */
void destroyController(Controller *ctrl);

/*
 * Getter for the repo field of the Controller struct
 * :ctrl: pointer to a Controller object
 * return: pointer to an OfferRepo object
 * */
OfferRepo *getRepo(Controller *ctrl);

/*
 * Function that implements the add function, using the .addRepo() function, taking into account any data validation (if
 * an offer already exists, it won't be added, and will return 0; return 1 otherwise).
 * :ctrl: Controller object
 * :type: pointer to char (can be "seaside", "mountain", "city break)"
 * :destination: pointer to char
 * :departureDate: Date variable
 * :price: double
 * return: 0, if NULL pointers encountered or the offer can't be added
 *         1, otherwise
 * */
int addController(Controller *ctrl, char *type, char *destination, Date departureDate, double price);

/*
 * Function that implements the delete function, using the .deleteRepo() function, taking into account any data validation (if
 * an offer does not exist, it won't be deleted, and will return 0; return 1 otherwise).
 * :ctrl: Controller object
 * :destination: pointer to char
 * :departureDate: Date variable
 * return: 0, if NULL pointers encountered or the offer can't be deleted
 *         1, otherwise
 * */
int deleteController(Controller *ctrl, char *destination, Date departureDate);

/*
 * Function that implements the update function, using the .updateRepo() function, taking into account any data validation (if
 * an offer does not exist, it won't be updated, and will return 0; return 1 otherwise).
 * :ctrl: Controller object
 * :newType: pointer to char (can be "seaside", "mountain", "city break)"
 * :destination: pointer to char
 * :departureDate: Date variable
 * :newPrice: double
 * return: 0, if NULL pointers encountered or the offer can't be updated
 *         1, otherwise
 * */
int updateController(Controller *ctrl, char *newType, char *destination, Date departureDate, double newPrice);

/*
 * Function that sorts the elements stored into the repo, using the Direct Selection Sort.
 * Runtime: O(n^2)
 * :ctrl: pointer to Controller object
 * */
void sort(Controller *ctrl, int sortOption);

/*
 * Function that generates 10 instances when starting the program.
 * :ctrl: pointer to Controller object
 * */
void generateInstances(Controller *ctrl);

/*
 * Function that filters the list of elements by type. A new repo containing the elements that satisfy the given
 * condition will be created and returned.
 * :repo: pointer to an OfferRepo object
 * :type: pointer to char (can be "seaside", "mountain" or "city break")
 * return: pointer to an OfferRepo object
 * */
OfferRepo *filterByType(OfferRepo *repo, char *type);

/*
 * Function that filters the list of elements by the departureDate. A new repo containing the elements that satisfy the
 * given condition will be created and returned.
 * :repo: pointer to an OfferRepo object
 * :departureDate: Date instance
 * return: pointer to an OfferRepo object
 * */
OfferRepo *filterByDate(OfferRepo *repo, Date departureDate);

/*
 * Function that filters the list of elements by price. A new repo containing the elements that satisfy the
 * given condition will be created and returned.
 * :repo: pointer to an OfferRepo object
 * :price: double
 * return: pointer to an OfferRepo object
 * */
OfferRepo *filterByPrice(OfferRepo *repo, double price);

/*
 * Function that implements the undo function. Based on each operation, we determine its reverse and push/pop the
 * operations in the corresponding stacks.
 * :ctrl: pointer to Controller object
 * return: int
 * */
int undo(Controller *ctrl);

/*
 * Function that implements the redo function. Based on each operation, we determine its reverse and push/pop the
 * operations in the corresponding stacks.
 * :ctrl: pointer to Controller object
 * return: int
 * */
int redo(Controller *ctrl);

#endif
