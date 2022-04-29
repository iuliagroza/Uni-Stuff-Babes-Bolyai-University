#include "Penguin.h"
#include "Dog.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include "Zoo.h"

using namespace std;

vector<Animal*> createAnimals()
{
	// Animal a{ "black", 20 }; //Animal is an abstract class; objects of this type can no longer be created

	vector<Animal*> animals;
	Animal* p1 = new Penguin{ "black", 7, "Magellanic" };
	Penguin* p2 = new Penguin{ "white and black", 6, "Emperor" };
	Dog* d1 = new Dog{ "black", 35, "rottweiler", 2 };
	Dog* d2 = new Dog{ "beige", 25, "Labrador retriever", 4 };

	animals.push_back(p1);
	animals.push_back(d1);
	animals.push_back(p2);
	animals.push_back(d2); 

	return animals;
}

void destroyAnimals(vector<Animal*> animals)
{
	for (auto a : animals)
		delete a;
}

void homogenousContainer()
{
	vector<Animal*> animals = createAnimals();

	for (auto a : animals)
	{
		// send the same message to all animals: to print their information and to speak
		cout << a->toString() << endl;
		a->speak();
		cout << endl;
	}

	destroyAnimals(animals);
}

// ------------------------------------------------------------------------------------------------------

void filterByCriterion(vector<Animal*> animals, Filter* f)
{
	for (auto a : animals)
		if (f->include(a))
			cout << a->toString();
}

void filterAnimals()
{
	vector<Animal*> animals = createAnimals();

	FilterWeightLessThan filterW{ 30 };
	FilterColour filterC{ "black" };

	cout << "Animals having weight less than 30: ";
	filterByCriterium(animals, &filterW);

	cout << "Black animals: ";
	filterByCriterium(animals, &filterC);

	destroyAnimals(animals);
}

// ------------------------------------------------------------------------------------------------------

int main()
{
	system("color f4");

	homogenousContainer();

	filterAnimals();

	_CrtDumpMemoryLeaks();

	system("pause");
	return 0;
}