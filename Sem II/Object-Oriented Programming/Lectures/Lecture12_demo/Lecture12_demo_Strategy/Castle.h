#pragma once
#include <string>

class Castle
{
private:
	std::string description;
	std::string location;
	int price;

public:
	Castle(std::string desc, std::string loc, int pr) : description{ desc }, location{ loc }, price{ pr }{}
	std::string getDescription() const { return this->description; }
	std::string getLocation() const { return this->location; }
	int getPrice() const { return this->price; }
};
