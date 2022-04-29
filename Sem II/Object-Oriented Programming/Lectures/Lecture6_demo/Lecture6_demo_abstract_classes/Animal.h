#pragma once
#include <string>

class Animal
{
protected:
	std::string colour;
	double weight;

public:
	Animal(std::string _colour, double _weight);
	virtual ~Animal();

	std::string getColour() const;
	double getWeight() const;

	virtual std::string toString() const;

	virtual void speak() const = 0;
};

