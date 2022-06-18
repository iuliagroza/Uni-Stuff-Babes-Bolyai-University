#include "Student.h"
#include <fstream>
#include <vector>
#include "Utils.h"

using namespace std;

istream & operator>>(istream & is, Student & s)
{
	string line;
	getline(is, line);

	vector<string> tokens = tokenize(line, ',');
	if (tokens.size() != 4) // make sure all the starship data was valid
		return is;

	s.name = tokens[0];
	s.group = tokens[1];
	s.labGrade = std::stod(tokens[2]);
	s.seminarGrade = std::stod(tokens[3]);

	return is;

}

ostream & operator<<(ostream & os, const Student & s)
{
	os << s.name << "," << s.group << "," << s.labGrade << "," << s.seminarGrade << "\n";
	return os;
}