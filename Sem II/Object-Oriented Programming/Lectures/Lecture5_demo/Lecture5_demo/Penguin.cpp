#include "Penguin.h"
#include <iostream>
#include <sstream>

using namespace std;

Penguin::Penguin(std::string _colour, double _weight, 
	std::string _type) : Animal{_colour, _weight}, type { _type }
{
	cout << "Constructing a "<<this->type<<" penguin, weighting "<<this->weight<<" kg and having the colours: "<<this->colour<<".\n\n";
}

Penguin::~Penguin()
{
	cout <<this->type<<" penguin, weighting "<<this->weight<<" kg and having the colours : "<<this->colour<<" is being destroyed.\n";
}

std::string Penguin::getType() const
{
	return this->type;
}

std::string Penguin::toString() const
{
	// access the function from the base class
	string baseStr = Animal::toString();

	string type = "Penguin \n\t type: " + this->type + "\n";
	return baseStr + type;
}
