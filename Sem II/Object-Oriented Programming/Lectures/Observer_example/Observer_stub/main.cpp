#include "Observer_stub.h"
#include <QtWidgets/QApplication>
#include "ShoppingBasketWidget.h"
#include "TotalWidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	ShoppingBasket basket{};
	basket.addProduct(Product{ "Apples", 18 });
	basket.addProduct(Product{ "Butter", 16 });
	basket.addProduct(Product{ "Orange juice", 22 });
	basket.addProduct(Product{ "Surgical mask", 3 });

	ShoppingBasketWidget w1{ basket };
	w1.show();
	ShoppingBasketWidget w2{ basket };
	w2.show();
	TotalWidget w3{ basket };
	w3.show();

	return a.exec();
}
