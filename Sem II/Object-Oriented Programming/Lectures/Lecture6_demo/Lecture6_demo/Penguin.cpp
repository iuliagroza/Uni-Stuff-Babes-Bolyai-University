#include "Penguin.h"
#include <iostream>
#include <sstream>

using namespace std;

Penguin::Penguin(std::string _colour, double _weight, std::string _type) : Animal{ _colour, _weight }, type{ _type }
{
	cout << "Constructing a "<<this->type<<" penguin, weighting "<<this->weight<<" kg and having the colours: "<<this->colour<<"." << endl;
}

Penguin::~Penguin()
{
	cout <<this->type<<" penguin, weighting "<<this->weight<<" kg and having the colours : "<<this->colour<<" is being destroyed." << endl;
}

std::string Penguin::getType() const
{
	return this->type;
}

std::string Penguin::toString() const
{
	// access the function from the base class
	string baseStr = Animal::toString();

	stringstream buffer;
	buffer << "Penguin \n\t type: " << this->type << endl;
	return baseStr + buffer.str();
}
