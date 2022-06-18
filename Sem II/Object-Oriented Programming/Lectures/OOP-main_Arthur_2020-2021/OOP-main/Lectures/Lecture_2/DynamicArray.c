#include "DynamicArray.h"
#include <stdlib.h>
#include <assert.h>

DynamicArray* createDynamicArray(int capacity)
{
	DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));
	// make sure that the space was allocated
	if (da == NULL)
		return NULL;

	da->capacity = capacity;
	da->length = 0;

	// allocate space for the elements
	da->elems = (TElement*)malloc(capacity * sizeof(TElement));
	if (da->elems == NULL)
		return NULL;

	return da;
}

void destroy(DynamicArray* arr)
{
	if (arr == NULL)
		return;

	// free the space allocated for the planets
	free(arr->elems);
	arr->elems = NULL;

	// free the space allocated for the dynamic array
	free(arr);
	//arr = NULL; // !!!
}

// Resizes the array, allocating more space.
void resize(DynamicArray* arr)
{
	// Implement this method...
}

void add(DynamicArray* arr, TElement t)
{
	if (arr == NULL)
		return;
	if (arr->elems == NULL)
		return;

	// resize the array, if necessary
	if (arr->length == arr->capacity)
		resize(arr);
	arr->elems[arr->length] = t;
	arr->length++;
}

void testsDynamicArray()
{
	DynamicArray* da = createDynamicArray(2);
	if (da == NULL)
		assert(0);

	assert(da->capacity == 2);
	assert(da->length == 0);

	Planet p1 = createPlanet("Wolf 1061 c", "terrestrial", 13.8);
	add(da, p1);
	assert(da->length == 1);

	Planet p2 = createPlanet("HAT-P-26b", "Neptune-like", 450);
	add(da, p2);
	assert(da->length == 2);

	// capacity must double
	Planet p3 = createPlanet("Proxima Centauri b", "terrestrial", 4.2);
	add(da, p3);
	assert(da->length == 3);
	assert(da->capacity == 4);

	destroy(da);
}