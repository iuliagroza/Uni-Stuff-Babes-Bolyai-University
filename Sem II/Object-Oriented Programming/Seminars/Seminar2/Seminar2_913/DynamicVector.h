#pragma once

#include "song.h"

typedef song TElem;

class DynamicVector
{
private:
	TElem* elems;
	int capacity, size;

public:
	DynamicVector(int capacity = 10);
	DynamicVector(const DynamicVector& v);

	DynamicVector& operator=(const DynamicVector& v);
	void add(const TElem& elem);
	void resize();

	TElem& operator[](int index) { return this->elems[index]; }

	int getSize() const { return this->size; }

	~DynamicVector();
};

