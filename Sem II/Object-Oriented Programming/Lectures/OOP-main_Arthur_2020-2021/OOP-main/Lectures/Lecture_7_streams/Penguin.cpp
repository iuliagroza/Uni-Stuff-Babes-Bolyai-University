#include "Penguin.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

namespace Lecture_7_streams {
    Penguin::Penguin(std::string _colour, double _weight, std::string _type, std::string _rankAndOccupation) : Animal{
            _colour, _weight}, type{_type}, rankAndOccupation{_rankAndOccupation} {
    }

    Penguin::~Penguin() {
    }

    std::string Penguin::getType() const {
        return this->type;
    }

    std::string Penguin::toString() const {
        // access the function from the base class
        string baseStr = Animal::toString();

        stringstream buffer;
        buffer << "Penguin \n\t type: " << this->type << endl;
        return baseStr + buffer.str();
    }

    ostream &operator<<(ostream &stream, const Penguin &p) {
        stream.width(20);
        stream << p.colour + " |";
        stream.width(10);
        stringstream strWeight;
        strWeight.precision(3);
        strWeight << p.weight << " |";
        stream << strWeight.str();
        stream.width(15);
        stream << p.type + " |";
        stream.width(25);
        stream << p.rankAndOccupation + " |";
        stream << endl;
        return stream;
    }

//ostream & operator<<(ostream & stream, const Penguin & p)
//{
//	stream << setw(20) << left << p.colour;
//	cout << "|";
//	stringstream strWeight;
//	strWeight.precision(3);
//	strWeight << p.weight;
//	stream << setw(10) << left << strWeight.str();
//	cout << "|";
//	stream << setw(15) << left << p.type;
//	cout << "|";
//	stream << setw(25) << left << p.rankAndOccupation;
//	cout << "|";
//	stream << endl;
//	return stream;
//}
}