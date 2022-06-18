#include "Product.h"

Product::Product(const std::string& name, double price): name{name}, price{price}
{
}

std::string Product::getName() const
{
	return this->name;
}

double Product::getPrice() const
{
	return this->price;
}

std::string Product::toString() const
{
	return this->name + " - " + std::to_string(this->price);
}
