#include "../headers/Person.h"

Person::Person() {

}

Person::Person(std::string &name, const double &income) : Client(name, income){
}

Person::~Person() {

}

bool Person::isInterested(Dwelling d) {
    return (d.get_price()/1000 <= this->income);
}

std::string Person::to_string() {
    return "Name: " + this->name + "; Price: " + std::to_string(this->income) + "\n";
}

double Person::totalIncome() {
    return this->income;
}
