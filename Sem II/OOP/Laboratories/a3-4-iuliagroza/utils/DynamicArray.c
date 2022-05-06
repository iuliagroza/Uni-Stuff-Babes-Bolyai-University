#include "DynamicArray.h"
#include <stdlib.h>
#include <string.h>

DynamicArray *createArray(int capacity) {
    DynamicArray *array = (DynamicArray *) malloc(sizeof(DynamicArray));
    // Handling NULL/dangling pointers
    if (array == NULL) {
        return NULL;
    }

    array->size = 0;

    array->capacity = capacity;

    array->elements = (TElem *) malloc(sizeof(TElem) * array->capacity);
    // Handling NULL/dangling pointers
    if (array->elements == NULL) {
        return NULL;
    }

    return array;
}

void destroyArray(DynamicArray *array) {
    if (array == NULL) {
        return;
    }

    int i;
    for(i=0; i<array->size; i++) {
        destroyOffer(array->elements[i]);
    }

    free(array->elements);
    free(array);
}

void doubleCapacity(DynamicArray *array) {
    DynamicArray *newArray = createArray(2 * array->capacity);

    newArray->size = array->size;

    for (int i = 0; i < newArray->size; i++) {
        newArray->elements[i] = array->elements[i];
    }

    destroyArray(array);

    array = newArray;

    destroyArray(newArray);
}

int getSizeArr(DynamicArray *array) {
    return array->size;
}

void add(DynamicArray *array, TElem element) {
    if (array->size == array->capacity) {
        doubleCapacity(array);
    }

    array->elements[array->size] = element;
    array->size++;
}

void delete(DynamicArray *array, int position) {
    int i;
    for (i = position; i < array->size - 1; i++) {
        array->elements[i] = array->elements[i + 1];
    }

    destroyOffer(array->elements[array->size - 1]);

    array->size--;
}

void update(DynamicArray *array, int position, TElem newElement) {
    array->elements[position] = newElement;
}

int find(DynamicArray *array, TElem element) {
    for (int i = 0; i < array->size; i++) {
        if (getDay(array->elements[i]) == getDay(element) &&
            getMonth(array->elements[i]) == getMonth(element) &&
            getYear(array->elements[i]) == getYear(element) &&
            strcmp(getDestination(array->elements[i]), getDestination(element)) == 0) {
            return i;
        }
    }

    return -1;
}