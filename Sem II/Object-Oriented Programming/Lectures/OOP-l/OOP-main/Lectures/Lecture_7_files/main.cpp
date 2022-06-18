#include <fstream>
#include <string>
#include <vector>
#include "Spaceship.h"

using namespace std;
using namespace Lecture_7_files;

void testRead()
{
	ifstream f("Names.txt");
	vector<string> names;
	string input;
	if (!f.is_open())
		return;
	while (!f.eof())
	{
		f >> input;
		names.push_back(input);
	}

	f.close();

	// names will contain the last name (David) twice
}

void testReadCorrected()
{
	ifstream f("Names.txt");
	vector<string> names;
	string input;
	if (!f.is_open())
		return;
	while (f >> input)
	{
		names.push_back(input);
	}
}

void readSpaceships()
{
	ifstream f("Spaceships.csv");
	if (!f.is_open())
		return;

	Spaceship s{};
	while (f >> s)
	{
		cout << s << endl;
	}

	f.close();
}

void writeSpaceShips()
{
	ofstream f("Spaceships.csv", ios::app);	// will append data
	if (!f.is_open())
		return;

	vector<Spaceship> spaceships = { Spaceship{"Death Star", "Darth Vader", "dreadnought"}, 
		Spaceship{"Prometheus", "George Hammond", "battlecruiser"},
		Spaceship{"USS Discovery", "Gabriel Lorca", "explorer"} };

	for (auto s : spaceships)
	{
		f << s;
	}

	f.close();
}

//int main()
//{
//	testRead();
//	testReadCorrected();
//
//	// make sure the user enters a value which can be converted to integer
//	int val{ 0 };
//	cout << "Please input an integer value: ";
//	while (!(cin >> val))
//	{
//		cout << "Please input an integer value: ";
//		cin.clear();			// reset the error flags
//		cin.ignore(100, '\n');	// extract characters from the input and discard them: either 100 characters or all characters up to encountering '\n'
//	}
//
//	readSpaceships();
//	writeSpaceShips();
//
//	return 0;
//}