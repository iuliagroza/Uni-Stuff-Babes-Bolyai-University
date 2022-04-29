#include "Tests.h"
#include "../controller/Controller.h"
#include <assert.h>
#include <stdlib.h>

void testDomain() {
    Date d;
    d.day = 12;
    d.month = 12;
    d.year = 2030;
    Offer *offer = createOffer("seaside", "aaa", d, 123.99);

    assert(offer != NULL);

    destroyOffer(offer);

    printf("testDomain() passed...\n");
}

void testDynamicArray() {
    DynamicArray *dynamicArray = createArray(10);

    assert(dynamicArray != NULL);

    destroyArray(dynamicArray);

    printf("testDynamicArray() passed...\n");
}

void testDoubleCapacity() {
    DynamicArray *dynamicArray = createArray(10);

    assert(dynamicArray != NULL);

    doubleCapacity(dynamicArray);

    assert(dynamicArray->capacity == 10);

    destroyArray(dynamicArray);

    printf("testDoubleCapacity() passed...\n");
}

void testFind() {
    Date d;
    d.day = 12;
    d.month = 12;
    d.year = 2030;
    Offer *offer = createOffer("seaside", "aaa", d, 123.99);

    assert(offer != NULL);

    DynamicArray *dynamicArray = createArray(10);

    assert(dynamicArray != NULL);

    int result = find(dynamicArray, offer);

    assert(result == -1);

    destroyOffer(offer);
    destroyArray(dynamicArray);

    printf("testDoubleCapacity() passed...\n");
}

void testRepo() {
    OfferRepo *repo = createRepo();

    assert(repo != NULL);

    destroyRepo(repo);

    printf("testRepo() passed...\n");
}

void testController() {
    OfferRepo *repo = createRepo();
    OperationStack *undoStack = createOperationStack();
    OperationStack *redoStack = createOperationStack();
    Controller *ctrl = createController(repo, undoStack, redoStack);

    assert(repo != NULL);
    assert(undoStack != NULL);
    assert(redoStack != NULL);
    assert(ctrl != NULL);

    destroyController(ctrl);

    printf("testController() passed...\n");
}

void testAddRepo() {
    Date d;
    d.day = 12;
    d.month = 12;
    d.year = 2030;
    Offer *offer = createOffer("seaside", "aaa", d, 123.99);

    assert(offer != NULL);

    OfferRepo *repo = createRepo();

    assert(repo != NULL);

    addRepo(repo, offer);

    assert(repo->offers->elements[getSize(repo)-1] == offer);

    destroyOffer(offer);
    destroyRepo(repo);

    printf("testAddRepo() passed...\n");
}

void testDeleteRepo() {
    Date d;
    d.day = 12;
    d.month = 12;
    d.year = 2030;
    Offer *offer = createOffer("seaside", "aaa", d, 123.99);

    assert(offer != NULL);

    OfferRepo *repo = createRepo();

    assert(repo != NULL);

    addRepo(repo, offer);
    deleteRepo(repo, offer->destination, offer->departureDate);

    assert(getSize(repo) == 0);

    destroyOffer(offer);
    destroyRepo(repo);

    printf("testDeleteRepo() passed...\n");
}

void testUpdateRepo() {
    Date d;
    d.day = 12;
    d.month = 12;
    d.year = 2030;
    Offer *offer = createOffer("seaside", "aaa", d, 123.99);

    d.day = 12;
    d.month = 12;
    d.year = 2030;
    Offer *newOffer = createOffer("mountain", "aaa", d, 78999);

    assert(offer != NULL);

    OfferRepo *repo = createRepo();

    assert(repo != NULL);

    addRepo(repo, offer);
    updateRepo(repo, newOffer);

    assert(repo->offers->elements[getSize(repo)-1] != offer);

    destroyOffer(offer);
    destroyOffer(newOffer);
    destroyRepo(repo);

    printf("testUpdateRepo() passed...\n");
}

void testAddController() {
    Date d;
    d.day = 12;
    d.month = 12;
    d.year = 2030;
    Offer *offer = createOffer("seaside", "aaa", d, 123.99);

    assert(offer != NULL);

    OfferRepo *repo = createRepo();
    OperationStack *undoStack = createOperationStack();
    OperationStack *redoStack = createOperationStack();
    Controller *ctrl = createController(repo, undoStack, redoStack);

    assert(repo != NULL);
    assert(undoStack != NULL);
    assert(redoStack != NULL);
    assert(ctrl != NULL);

    addController(ctrl, offer->type, offer->destination, offer->departureDate, offer->price);

    assert(ctrl->repo->offers->elements[getSize(ctrl->repo)-1] != offer);

    destroyOffer(offer);
    destroyController(ctrl);

    printf("testAddController() passed...\n");
}

void testDeleteController() {
    Date d;
    d.day = 12;
    d.month = 12;
    d.year = 2030;
    Offer *offer = createOffer("seaside", "aaa", d, 123.99);

    assert(offer != NULL);

    OfferRepo *repo = createRepo();
    OperationStack *undoStack = createOperationStack();
    OperationStack *redoStack = createOperationStack();
    Controller *ctrl = createController(repo, undoStack, redoStack);

    assert(repo != NULL);
    assert(undoStack != NULL);
    assert(redoStack != NULL);
    assert(ctrl != NULL);

    addController(ctrl, offer->type, offer->destination, offer->departureDate, offer->price);
    deleteController(ctrl, offer->destination, offer->departureDate);

    assert(getSize(ctrl->repo) == 0);

    destroyOffer(offer);
    destroyController(ctrl);

    printf("testDeleteController() passed...\n");
}

void testUpdateController() {
    Date d;
    d.day = 12;
    d.month = 12;
    d.year = 2030;
    Offer *offer = createOffer("seaside", "aaa", d, 123.99);

    assert(offer != NULL);

    OfferRepo *repo = createRepo();
    OperationStack *undoStack = createOperationStack();
    OperationStack *redoStack = createOperationStack();
    Controller *ctrl = createController(repo, undoStack, redoStack);

    assert(repo != NULL);
    assert(undoStack != NULL);
    assert(redoStack != NULL);
    assert(ctrl != NULL);

    addController(ctrl, offer->type, offer->destination, offer->departureDate, offer->price);
    updateController(ctrl, "mountain", offer->destination, offer->departureDate, 1999.87);

    assert(ctrl->repo->offers->elements[getSize(ctrl->repo)-1] != offer);

    destroyOffer(offer);
    destroyController(ctrl);

    printf("testUpdateController() passed...\n");
}

void testAll() {
    testDomain();
    testDynamicArray();
    testDoubleCapacity();
    testFind();
    testRepo();
    testAddRepo();
    testDeleteRepo();
    testUpdateRepo();
    testController();
    testAddController();
    testDeleteController();
    testUpdateController();
    printf("All tests passed!\n");
}
