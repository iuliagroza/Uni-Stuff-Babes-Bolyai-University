#include "../headers/Client.h"

#include <utility>

Person::Person(double inc, const std::string &nam) {
    this->income = inc;
    this->name = nam;
}

bool Person::isInterested(Dwelling* d) {
    return d->getPrice()/1000<= this->totalIncome();
}

std::string Person::to_string() {
    std::string f;
    f += "name: " + this->name + "  income: " + std::to_string(this->income) + "  total: " + std::to_string(this->totalIncome());
    return f;
}

Company::Company(double inc, std::string nam, double money) {
    this->moneyFromInvestments = money;
    this->income = inc;
    this->name = std::move(nam);

}

bool Company::isInterested(Dwelling* d) {
    return (d->getPrice()/100<= this->totalIncome()) and d->getProfitable();
}

std::string Company::to_string() {
    std::string f;
    f += "name: " + this->name + "  income: " + std::to_string(this->income) + "  money: " + std::to_string(this->moneyFromInvestments)+ "  total: " + std::to_string(this->totalIncome());
    return f;
}
