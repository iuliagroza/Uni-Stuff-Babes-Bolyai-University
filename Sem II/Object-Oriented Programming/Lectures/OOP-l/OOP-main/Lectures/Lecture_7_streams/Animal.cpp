#include "Animal.h"
#include <sstream>
#include <iostream>

using namespace std;

namespace Lecture_7_streams {
    Animal::Animal(std::string _colour, double _weight) : colour{_colour}, weight{_weight} {
    }

    Animal::~Animal() {
    }

    std::string Animal::getColour() const {
        return this->colour;
    }

    double Animal::getWeight() const {
        return this->weight;
    }

    std::string Animal::toString() const {
        stringstream buffer;
        buffer << "Animal \n\t weight: " << this->weight << " kg" << endl << "\t colour: " << this->colour << endl;
        return buffer.str();
    }

    istream &operator>>(istream &stream, Animal &a) {
        stream >> a.colour >> a.weight;
        return stream;
    }

    ostream &operator<<(ostream &stream, const Animal &a) {
        stream << a.weight << ", " << a.colour << endl;
        return stream;
    }
}