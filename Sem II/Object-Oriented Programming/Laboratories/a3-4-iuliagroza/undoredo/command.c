#include "command.h"
#include <string.h>
#include <stdlib.h>

Operation *createOperation(Offer *offer, char *type) {
    Operation *operation = (Operation *) malloc(sizeof(Operation));
    operation->offer = offer;
    operation->type = (char *) malloc(sizeof(char) * strlen(type) + 1);
    strcpy(operation->type, type);

    return operation;
}

void destroyOperation(Operation *operation) {
    destroyOffer(operation->offer);
    free(operation->type);
    free(operation);
}

Operation *operationCopy(Operation *operation) {
    Operation *newOperation = createOperation(getOperationOffer(operation), getOperationType(operation));
    return newOperation;
}

char *getOperationType(Operation *operation) {
    return operation->type;
}

Offer *getOperationOffer(Operation *operation) {
    return operation->offer;
}

OperationStack *createOperationStack() {
    OperationStack *stack = (OperationStack *) malloc(sizeof(OperationStack));
    // Handling NULL/dangling pointers
    if (stack == NULL) {
        return NULL;
    }

    stack->operations = createArray(10);

    return stack;
}

void destroyOperationStack(OperationStack *stack) {
    destroyArray(stack->operations);
    free(stack);
}

void push(OperationStack *stack, Operation *operation) {
    Operation *newOperation = operationCopy(operation);
    add(stack->operations, newOperation);
    destroyOperation(newOperation);
}

Operation *pop(OperationStack *stack) {
    if (getSizeArr(stack->operations) == 0)
        return NULL;

    Operation *operation = stack->operations->elements[stack->operations->size - 1];
    stack->operations->size--;

    return operation;
}