#include "Penguin.h"
#include "Dog.h"
#include <Windows.h>
#include <iostream>
#include <crtdbg.h>

using namespace std;

void virtualFunctions()
{
	Animal a1{"black" , 20};
	Penguin p1{ "black and white" , 7 , "Magellanic" };
	Animal* a2 = &p1;
	cout << a2->toString();

	Animal* Skipper = new Penguin{ "black and white", 7, "Magellanic" };
	cout << Skipper->toString() << endl;

	Animal& d{Dog{ "black", 25, "rottweiler", 0.2 }};
	cout << d.toString() << endl;

	Animal x(*Skipper);
	cout << x.toString() << endl; // polymorphism does NOT work with objects!

	delete Skipper;
}

// ------------------------------------------------------------------------------------------------------

void virtualDestructors()
{
	Animal* a = new Animal{ "brown", 1 };
	Animal* a1 = new Penguin{ "black and white", 7, "Magellanic" };
	Animal* a2 = new Dog{ "black", 25, "rottweiler", 0.2 };

	delete a;
	delete a1;
	delete a2;
}

// ------------------------------------------------------------------------------------------------------

void upCasting()
{
	// all the casts are implicit

	Penguin Rico{ "black and white", 7, "Magellanic" };
	Animal a1{ Rico };
	cout << a1.toString() << endl;

	Dog d{ "black", 25, "rottweiler", 0.2 };
	Animal& a2{ d };
	cout << a2.toString() << endl;

	Penguin* Kowalski = new Penguin{ "white and black", 5, "Imperial" };
	Animal* a3{ Kowalski };
	cout << a3->toString() << endl;

	delete Kowalski;
}

// ------------------------------------------------------------------------------------------------------

void downCasting()
{
	Animal* a1 = new Penguin{ "black and white", 7, "Magellanic" };
	Penguin* p1 = static_cast<Penguin*>(a1);	// Valid! p1 is a valid and correct pointer to a Penguin
	Penguin* p2 = dynamic_cast<Penguin*>(a1);   // Valid! p2 is a valid and correct pointer to a Penguin

	Animal* a2 = new Animal{ "brown", 5 };
	Penguin* p3 = static_cast<Penguin*>(a2);	// works, but it generates undefined behaviour => DANGEROUS!
	// cout << p3->getType() << endl;	// !!! 
	Penguin* p4 = dynamic_cast<Penguin*>(a2);   // cast fails => p4 is now a nullptr
	if (p4 == nullptr)
	{
		cout << "Dynamic cast failed." << endl;
	}

	delete a1;
	delete a2;
}

// ------------------------------------------------------------------------------------------------------

int main()
{
	system("color f4");

	virtualFunctions();
	system("cls");

	virtualDestructors();
	system("cls");

	upCasting();
	system("cls");

	downCasting();

	_CrtDumpMemoryLeaks();

 	system("pause");
	return 0;
}