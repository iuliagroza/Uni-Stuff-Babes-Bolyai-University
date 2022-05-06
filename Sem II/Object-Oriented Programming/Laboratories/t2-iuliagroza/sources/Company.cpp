#include "../headers/Company.h"

Company::Company() {

}

Company::Company(std::string &name, const double &income, const double &moneyFromInvestments) : Client(name, income), moneyFromInvestments(moneyFromInvestments) {
}

Company::~Company() {

}

double Company::totalIncome() {
    return this->income + this->moneyFromInvestments;
}

std::string Company::to_string() {
    return "Name: " + this->name + "; Price: " + std::to_string(this->income) + "; Money from investments: " + std::to_string(this->moneyFromInvestments) + "\n";
}

bool Company::isInterested(Dwelling d) {
    return ((d.get_price()/100 <= this->totalIncome()) && d.get_is_profitable());
}
