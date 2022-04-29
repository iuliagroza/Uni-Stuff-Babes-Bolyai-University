#pragma once
#include "DynamicVector.h"
#include "song.h"

class repo
{
private:
	DynamicVector list;

public:
	void add(const song& elem);
	int getSize() const { return list.getSize(); }
};

