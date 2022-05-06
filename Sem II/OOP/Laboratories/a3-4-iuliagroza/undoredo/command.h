#ifndef A3_4_IULIAGROZA_COMMAND_H
#define A3_4_IULIAGROZA_COMMAND_H

#include "../utils/DynamicArray.h"

typedef struct {
    Offer *offer;
    char *type;
} Operation;

typedef struct {
    DynamicArray *operations;
} OperationStack;

/*
 * Function that creates an operation, allocates memory for it and returns a pointer to it.
 * :offer: pointer to an Offer object
 * :type: pointer to char
 * return: pointer to Operation object
 * */
Operation *createOperation(Offer *offer, char *type);

/*
 * Function that destroys an operation and deallocates its memory.
 * :operation: pointer to an Operation object
 * */
void destroyOperation(Operation *operation);

/*
 * Function that copies an operation and returns a pointer to it.
 * :operation: pointer to Operation object
 * return: pointer to Operation object
 * */
Operation *operationCopy(Operation *operation);

/*
 * Getter for the Offer* field of the Operation struct.
 * :operation: pointer to Operation object
 * return: pointer to Offer object
 * */
Offer *getOperationOffer(Operation *operation);

/*
 * Getter for the type field of the Operation struct.
 * :operation: pointer to Operation object
 * return: pointer to char
 * */
char *getOperationType(Operation *operation);

/*
 * Creates an OperationStack object, allocates memory for it and returns it.
 * return: pointer to an OperationStack object
 * */
OperationStack *createOperationStack();

/*
 * Destroys an OperationStack object and deallocates its memory.
 * :stack: pointer to an OperationStack object
 * */
void destroyOperationStack(OperationStack *stack);

/*
 * Pushes an operation onto the stack.
 * :stack: pointer to an OperationStack object
 * :operation: pointer to an Operation objects
 * */
void push(OperationStack *stack, Operation *operation);

/*
 * Pops an operation from the stack and returns it.
 * :stack: pointer to an OperationStack object
 * return: pointer to an Operation object
 * */
Operation *pop(OperationStack *stack);

#endif
