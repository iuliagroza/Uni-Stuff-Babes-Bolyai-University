#pragma once
#include "repo.h"
#include <string>

class service
{
	repo& r;
public:
	service(repo& rep);
	void add(std::string name, std::string artist, double duration, std::string link);
	int getSize() const { return r.getSize(); }
};

