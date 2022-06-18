#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	//TODO - Representation
    int current_position;
    struct Node* current_element;
    TComp* copy_elems;
    int copy_current_position;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

