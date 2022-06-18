#pragma once
#include <string>

class Animal
{
protected:
	std::string colour;
	double weight;

public:
	Animal(const std::string& _colour, double _weight);
	~Animal();

	std::string getColour() const;
	double getWeight() const;

	std::string toString() const;
};

