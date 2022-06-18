#include <iostream>
#include "Animal.h"
#include "Penguin.h"
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;
using namespace Lecture_7_streams;

void overloadIOOperators()
{
	Animal a1{};
	cout << "Please input the data for the animal (first colour, then weight): " << endl;
	cin >> a1;
	
	cout << "The animal's attributes: ";
	cout << a1;

	// we can also chain
	Animal a2{};
	cout << "Please input the data for two animals (first colour, then weight): " << endl;
	cin >> a1 >> a2;
	cout << "The animals are: " << endl;
	cout << a1 << endl << a2 << endl;
}

// ------------------------------------------------------------------------------------------------------------

void formatOutput() 
{
	cout.width(5);
	cout << "1";
	cout.width(5);
	cout << "22" << endl;

	char prev = cout.fill('0');
	cout.width(10);
	cout << 25 << '\n';
	cout.fill(prev);

	const double PI = 3.1415926535897;
	cout.precision(3);
	cout << PI << endl;
	cout.precision(8);
	cout << PI << endl;
}

// ------------------------------------------------------------------------------------------------------------

void printHeaderForPenguinData()
{
	// print header
	cout.width(20);
	cout << "Colour |";
	cout.width(10);
	cout << "Weight |";
	cout.width(15);
	cout << "Type |";
	cout.width(25);
	cout << "Rank and occupation |";
	cout << endl;
	char prev = cout.fill('-');
	cout.width(70);
	cout << "";
	cout.fill(prev);
	cout << endl;
}

void printHeaderForPenguinDataManipulators()
{
	// print header
	cout << right << setw(20) << "Colour |";
	cout << right << setw(10) << right << "Weight |";
	cout << right << setw(15) << "Type |";
	cout << right << setw(25) << "Rank and occupation |";
	cout << endl;
	char prev = cout.fill();
	cout << setw(74) << setfill('-') << "" << endl;
	cout.fill(prev);
}

// ------------------------------------------------------------------------------------------------------------

void formattedPenguinData()
{
	Penguin Skipper{ "black and white", 5.2536, "Emperor", "commander" };
	Penguin Kowalski{ "black and white", 4.5812, "Adelie", "tactician" };
	Penguin Rico{ "color - crazy", 4.00, "Emperor", "demolition expert" };
	Penguin Private{ "white and black", 4.0212, "Magellanic", "cuteness bringer" };

	printHeaderForPenguinData();

	vector<Penguin> penguins = { Skipper, Kowalski, Rico, Private };
	for (auto p : penguins)
	{
		cout << p;
	}
	cout << endl;
}

void formattedPenginDataManipulators()
{
	Penguin Skipper{ "black and white", 5.2536, "Emperor", "commander" };
	Penguin Kowalski{ "black and white", 4.5812, "Adelie", "tactician" };
	Penguin Rico{ "color - crazy", 4.00, "Emperor", "demolition expert" };
	Penguin Private{ "white and black", 4.0212, "Magellanic", "cuteness bringer" };

	printHeaderForPenguinDataManipulators();

	vector<Penguin> penguins = { Skipper, Kowalski, Rico, Private };
	for (auto p : penguins)
	{
		cout << p;
	}
	cout << endl;
}

// ------------------------------------------------------------------------------------------------------------

ostream& doubleTabManipulator(ostream& os)
{
	os << "\t\t";
	return os;
}

void testTabManipulator()
{
	Penguin Skipper{ "black and white", 5.2536, "Emperor", "commander" };
	cout << Skipper.getWeight() << doubleTabManipulator << Skipper.getType() << endl;
}

// ------------------------------------------------------------------------------------------------------------

//int main()
//{
//	overloadIOOperators();
//
//	formatOutput();
//
//	formattedPenguinData();
//
//	formattedPenginDataManipulators();
//
//	testTabManipulator();
//	return 0;
//}