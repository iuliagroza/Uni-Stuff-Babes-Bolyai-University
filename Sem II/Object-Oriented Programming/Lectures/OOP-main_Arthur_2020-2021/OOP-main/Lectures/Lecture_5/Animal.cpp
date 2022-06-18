#include "Animal.h"
#include <sstream>
#include <iostream>

using namespace std;

Animal::Animal(const std::string& _colour, double _weight) : colour{ _colour }, weight{ _weight }
{
	cout << "Constructing an animal.\n";
}

Animal::~Animal()
{
	cout << "Animal is being destroyed.\n\n";
}

std::string Animal::getColour() const
{
	return this->colour;
}

double Animal::getWeight() const
{
	return this->weight;
}

std::string Animal::toString() const
{
	stringstream buffer;
	buffer << "Animal \n\t weight: " << this->weight << " kg"<< endl << "\t colour: " << this->colour << endl;
	return buffer.str();
}
