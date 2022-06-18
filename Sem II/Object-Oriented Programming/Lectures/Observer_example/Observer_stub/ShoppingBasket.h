#pragma once
#include <vector>
#include "Product.h"
#include "Observer.h"

class ShoppingBasket: public Subject
{
private:
	std::vector<Product> products;

public:
	void addProduct(const Product& prod);
	std::vector<Product> getAll() const;
	int getSize() const;
};

