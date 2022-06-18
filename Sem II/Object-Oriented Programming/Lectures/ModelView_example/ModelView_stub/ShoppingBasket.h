#pragma once
#include <vector>
#include "Product.h"

class ShoppingBasket
{
private:
	std::vector<Product> products;

public:
	void addProduct(const Product& prod);
	std::vector<Product> getAll() const;
	int getSize() const;
	void clear();
};