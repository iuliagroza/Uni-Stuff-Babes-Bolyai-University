#include "Controller.h"
#include <string.h>

Controller *createController(OfferRepo *repo, OperationStack *undoStack, OperationStack *redoStack) {
    // Handling NULL/dangling pointers
    if (repo == NULL || undoStack == NULL || redoStack == NULL) {
        return NULL;
    }

    Controller *ctrl = (Controller *) malloc(sizeof(Controller));
    // Handling NULL/dangling pointers
    if (ctrl == NULL) {
        return NULL;
    }

    ctrl->repo = repo;
    ctrl->undoStack = undoStack;
    ctrl->redoStack = redoStack;

    return ctrl;
}

void destroyController(Controller *ctrl) {
    // Handling NULL/dangling pointers
    if (ctrl == NULL) {
        return;
    }

    destroyRepo(ctrl->repo);
    destroyOperationStack(ctrl->undoStack);
    destroyOperationStack(ctrl->redoStack);
    free(ctrl);
}

OfferRepo *getRepo(Controller *ctrl) {
    return ctrl->repo;
}

int addController(Controller *ctrl, char *type, char *destination, Date departureDate, double price) {
    Offer *offer = createOffer(type, destination, departureDate, price);
    int result = addRepo(ctrl->repo, offer);
    destroyOffer(offer);

    if (result == 1) {
        Operation *operation = createOperation(offer, "add");
        push(ctrl->undoStack, operation);
        destroyOperation(operation);
        destroyOperationStack(ctrl->redoStack);
        ctrl->redoStack = createOperationStack();
    }

    return result;
}

int deleteController(Controller *ctrl, char *destination, Date departureDate) {
    Offer *result = deleteRepo(ctrl->repo, destination, departureDate);

    if (result != NULL) {
        Operation *operation = createOperation(result, "del");
        push(ctrl->undoStack, operation);
        destroyOperation(operation);
        destroyOperationStack(ctrl->redoStack);
        ctrl->redoStack = createOperationStack();
        return 1;
    }

    return 0;
}

int updateController(Controller *ctrl, char *newType, char *destination, Date departureDate, double newPrice) {
    Offer *offer = createOffer(newType, destination, departureDate, newPrice);
    Offer *result = updateRepo(ctrl->repo, offer);
    destroyOffer(offer);

    if (result != NULL) {
        Operation *operation = createOperation(result, "update");
        push(ctrl->undoStack, operation);
        destroyOperation(operation);
        destroyOperationStack(ctrl->redoStack);
        ctrl->redoStack = createOperationStack();

        return 1;
    }

    return 0;
}

void sort(Controller *ctrl, int sortOption) {
    int n = getSize(ctrl->repo);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((sortOption && getPrice(ctrl->repo->offers->elements[i]) > getPrice(ctrl->repo->offers->elements[j])) ||
                (!sortOption &&
                 getPrice(ctrl->repo->offers->elements[i]) < getPrice(ctrl->repo->offers->elements[j]))) {
                Offer *aux = ctrl->repo->offers->elements[i];
                ctrl->repo->offers->elements[i] = ctrl->repo->offers->elements[j];
                ctrl->repo->offers->elements[j] = aux;
            }
        }
    }
}

void generateInstances(Controller *ctrl) {
    Date d;

    d.day = 5;
    d.month = 10;
    d.year = 2022;
    Offer *offer = createOffer("seaside", "Santorini", d, 123.44);
    addRepo(getRepo(ctrl), copyOffer(offer));
    destroyOffer(offer);

    d.day = 16;
    d.month = 2;
    d.year = 2023;
    offer = createOffer("seaside", "Lima", d, 3000);
    addRepo(getRepo(ctrl), copyOffer(offer));
    destroyOffer(offer);

    d.day = 17;
    d.month = 10;
    d.year = 2022;
    offer = createOffer("mountain", "Cortina d'Ampezzo", d, 679.99);
    addRepo(getRepo(ctrl), copyOffer(offer));
    destroyOffer(offer);

    d.day = 30;
    d.month = 11;
    d.year = 2023;
    offer = createOffer("city break", "Paris", d, 69);
    addRepo(getRepo(ctrl), copyOffer(offer));
    destroyOffer(offer);

    d.day = 19;
    d.month = 8;
    d.year = 2022;
    offer = createOffer("seaside", "Rio de Janeiro", d, 781.11);
    addRepo(getRepo(ctrl), copyOffer(offer));
    destroyOffer(offer);

    d.day = 12;
    d.month = 7;
    d.year = 2025;
    offer = createOffer("city break", "Tokyo", d, 1000);
    addRepo(getRepo(ctrl), copyOffer(offer));
    destroyOffer(offer);

    d.day = 18;
    d.month = 12;
    d.year = 2028;
    offer = createOffer("mountain", "Poiana Brasov", d, 9999);
    addRepo(getRepo(ctrl), copyOffer(offer));
    destroyOffer(offer);

    d.day = 10;
    d.month = 10;
    d.year = 2026;
    offer = createOffer("mountain", "Zermatt", d, 888.9);
    addRepo(getRepo(ctrl), copyOffer(offer));
    destroyOffer(offer);

    d.day = 15;
    d.month = 3;
    d.year = 2024;
    offer = createOffer("city break", "New York City", d, 390);
    addRepo(getRepo(ctrl), copyOffer(offer));
    destroyOffer(offer);

    d.day = 19;
    d.month = 12;
    d.year = 2025;
    offer = createOffer("seaside", "Rimini", d, 28.46);
    addRepo(getRepo(ctrl), copyOffer(offer));
    destroyOffer(offer);
}

OfferRepo *filterByType(OfferRepo *repo, char *type) {
    // Handling NULL/dangling pointers
    if (repo == NULL || type == NULL) {
        return NULL;
    }

    OfferRepo *newRepo = createRepo();

    for (int i = 0; i < getSize(repo); i++) {
        if (strcmp(getType(repo->offers->elements[i]), type) == 0) {
            addRepo(newRepo, repo->offers->elements[i]);
        }
    }

    return newRepo;
}

/*
 * Function that checks if dateY is after dateX.
 * :dayX: integer (we know the input is valid)
 * :monthX: integer (we know the input is valid)
 * :yearX: integer (we know the input is valid)
 * :dayY: integer (we know the input is valid)
 * :monthY: integer (we know the input is valid)
 * :yearY: integer (we know the input is valid)
 * return: 0, if dateY is not after dateX
 *         1, otherwise
 * */
int validateLaterDate(int dayX, int monthX, int yearX, int dayY, int monthY, int yearY) {
    return ((yearY > yearX) || (yearY == yearX && ((monthY > monthX) || (monthY == monthX && dayY > dayX))));
}

OfferRepo *filterByDate(OfferRepo *repo, Date departureDate) {
    // Handling NULL/dangling pointers
    if (repo == NULL) {
        return NULL;
    }

    OfferRepo *newRepo = createRepo();

    for (int i = 0; i < getSize(repo); i++) {
        if (validateLaterDate(departureDate.day, departureDate.month, departureDate.year,
                              getDay(repo->offers->elements[i]), getMonth(repo->offers->elements[i]),
                              getYear(repo->offers->elements[i]))) {
            addRepo(newRepo, repo->offers->elements[i]);
        }
    }

    destroyRepo(repo);

    return newRepo;
}

OfferRepo *filterByPrice(OfferRepo *repo, double price) {
    // Handling NULL/dangling pointers
    if (repo == NULL) {
        return NULL;
    }

    OfferRepo *newRepo = createRepo();

    for (int i = 0; i < getSize(repo); i++) {
        if (getPrice(repo->offers->elements[i]) <= price) {
            addRepo(newRepo, repo->offers->elements[i]);
        }
    }

    return newRepo;
}

int undo(Controller *ctrl) {
    if (getSizeArr(ctrl->undoStack->operations) == 0) {
        return 0;
    }

    Operation *operation = pop(ctrl->undoStack);
    Operation *redoOperation = operationCopy(operation);

    if (strcmp(getOperationType(operation), "add") == 0) {
        strcpy(redoOperation->type, "del");
        Offer *offer = copyOffer(getOperationOffer(operation));
        deleteRepo(ctrl->repo, offer->destination, offer->departureDate);
        destroyOffer(offer);
    } else if (strcmp(getOperationType(operation), "del") == 0) {
        strcpy(redoOperation->type, "add");
        Offer *offer = copyOffer(getOperationOffer(operation));
        addRepo(ctrl->repo, offer);
        destroyOffer(offer);
    } else if (strcmp(getOperationType(operation), "update") == 0) {
        Offer *offer = copyOffer(getOperationOffer(operation));
        redoOperation->offer = copyOffer(updateRepo(ctrl->repo, offer));
        destroyOffer(offer);
    }

    push(ctrl->redoStack, redoOperation);
    destroyOperation(redoOperation);
    destroyOperation(operation);
    return 1;
}

int redo(Controller *ctrl) {
    if (getSizeArr(ctrl->redoStack->operations) == 0) {
        return 0;
    }

    Operation *operation = pop(ctrl->redoStack);
    Operation *undoOperation = operationCopy(operation);

    if (strcmp(getOperationType(operation), "add") == 0) {
        strcpy(undoOperation->type, "del");
        Offer *offer = copyOffer(getOperationOffer(operation));
        deleteRepo(ctrl->repo, offer->destination, offer->departureDate);
        destroyOffer(offer);
    } else if (strcmp(getOperationType(operation), "del") == 0) {
        strcpy(undoOperation->type, "add");
        Offer *offer = copyOffer(getOperationOffer(operation));
        addRepo(ctrl->repo, offer);
        destroyOffer(offer);
    } else if (strcmp(getOperationType(operation), "update") == 0) {
        Offer *offer = copyOffer(getOperationOffer(operation));
        undoOperation->offer = copyOffer(updateRepo(ctrl->repo, offer));
        destroyOffer(offer);
    }

    push(ctrl->undoStack, undoOperation);
    destroyOperation(undoOperation);
    destroyOperation(operation);
    return 1;
}