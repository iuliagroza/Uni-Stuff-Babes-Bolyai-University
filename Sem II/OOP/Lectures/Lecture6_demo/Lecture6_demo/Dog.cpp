#include "Dog.h"
#include <iostream>
#include <sstream>

using namespace std;

Dog::Dog(std::string _colour, double _weight, string _breed, double _furLength) : Animal{ _colour, _weight }, breed{ _breed }, furLength{ _furLength}
{
	cout << "Constructing a dog, breed " << this->breed<< " weighting " << this->weight << " kg, having the colours: " << this->colour << " and the fur length "<<this->furLength<<" cm." << endl;
}

string Dog::getBreed() const
{
	return this->breed;
}

double Dog::getFurLength() const
{
	return this->furLength;
}

std::string Dog::toString() const
{
	stringstream buffer;
	buffer << "Dog \n\t weight: " << this->weight <<" kg " << endl << "\t colour: " << this->colour << endl <<"\t breed: " << this->breed << endl << "\t fur length: " << this->furLength << " cm." << endl;
	return buffer.str();
}

Dog::~Dog()
{
	cout << "Dog: breed " << this->breed << " weighting " << this->weight << " kg, having the colours: " << this->colour << " and the fur length " << this->furLength << " cm is being destroyed." << endl;
}