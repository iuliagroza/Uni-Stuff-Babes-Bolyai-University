#include "../headers/Dwelling.h"

Dwelling::Dwelling() {

}

Dwelling::Dwelling(const double &price, const bool &isProfitable) {
    this->price = price;
    this->isProfitable = isProfitable;
}

Dwelling::~Dwelling() {

}

bool Dwelling::get_is_profitable() {
    return this->isProfitable;
}

double Dwelling::get_price() {
    return this->price;
}