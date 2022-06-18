#include "Penguin.h"
#include <iostream>
#include <sstream>

namespace abstract_base_class {
    using namespace std;

    Penguin::Penguin(std::string _colour, double _weight, std::string _type) : Animal{_colour, _weight}, type{_type} {
        //cout << "Constructing a "<<this->type<<" penguin, weighting "<<this->weight<<" kg and having the colours: "<<this->colour<<"." << endl;
    }

    Penguin::~Penguin() {
        //cout <<this->type<<" penguin, weighting "<<this->weight<<" kg and having the colours : "<<this->colour<<" is being destroyed." << endl;
    }

    std::string Penguin::getType() const {
        return this->type;
    }

    std::string Penguin::toString() const {
        stringstream buffer;
        buffer << "Penguin \n\t weight : " << this->weight << " kg" << endl << "\t colour : " << this->colour << endl
               << "\t type: " << this->type << endl;
        return buffer.str();
    }

    void Penguin::speak() const {
        cout << "Penguin speaking: Gaw gaw" << endl;
    }
}