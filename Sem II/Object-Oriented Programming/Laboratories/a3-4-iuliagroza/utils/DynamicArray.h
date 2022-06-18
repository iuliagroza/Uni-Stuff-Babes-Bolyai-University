#ifndef A3_4_IULIAGROZA_DYNAMICARRAY_H
#define A3_4_IULIAGROZA_DYNAMICARRAY_H

#include "../domain/Offer.h"

typedef void *TElem;

/*
 * Struct that stores a dynamic array with elements of TElem type.
 * */
typedef struct {
    int size;
    int capacity;
    TElem *elements;
} DynamicArray;

/*
 * Function that creates a DynamicArray object and allocates memory for it and implicitly for its fields.
 * return: pointer to a DynamicArray object.
 * */
DynamicArray *createArray();

/*
 * Function that destroys a destroyArray object and deallocates its memory and implicitly its fields.
 * :array: pointer to a DynamicArray object
 * */
void destroyArray(DynamicArray *array);

/*
 * Function that doubles the capacity of the array when size reaches capacity. A new array with double capacity is
 * created, all the elements of the initial; array are copied into the new one and the initial one is destroyed.
 * :array: pointer to a DynamicArray object
 * return: pointer to a DynamicArray object
 * */
void doubleCapacity(DynamicArray *array);

/*
 * Getter for the sizeArr field of the DynamicArray struct
 * :offer: pointer to a DynamicArray object
 * return: int
 * */
int getSizeArr(DynamicArray *array);

/*
 * Function that implements the add functionality.
 * :array: pointer to a DynamicArray object
 * :element: TElem
 * */
void add(DynamicArray *array, TElem element);

/*
 * Function that implements the delete functionality.
 * :array: pointer to a DynamicArray object
 * :position: int (the position of the element to be deleted)
 * */
void delete(DynamicArray *array, int position);

/*
 * Function that implements the update functionality.
 * :array: pointer to a DynamicArray object
 * :position: int (the position of the element to be updated)
 * :newElement: TElem (updated content of the element)
 * */
void update(DynamicArray *array, int position, TElem newElement);

/*
 * Function to search an element inside the dynamic array, If the element is found, we will return its position.
 * Otherwise, it will return -1.
 * :array: pointer to DynamicArray object
 * :element: TElem
 * return: int - position, if element is found
 *               -1, otherwise*/
int find(DynamicArray *array, TElem element);

#endif
