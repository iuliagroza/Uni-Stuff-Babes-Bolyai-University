#pragma once
#include "SLLArr.h"

class SLLA;

class Iterator {
private:
	Iterator(const SLLA& );
	const SLLA& slla;
	int current;
public:
	friend class SLLA;
	void first();
	void next();
	bool valid() const;
	TElem getCurrent() const;
};


