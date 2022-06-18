#include "TotalWidget.h"
#include <algorithm>

TotalWidget::TotalWidget(ShoppingBasket& basket, QWidget *parent)
	: QWidget(parent), basket{basket}
{
	ui.setupUi(this);

	basket.addObserver(this);

	this->update();
}

TotalWidget::~TotalWidget()
{
}

void TotalWidget::update()
{
	this->ui.noProducts->setText(QString::number(basket.getSize()));

	std::vector<Product> products = this->basket.getAll();
	double total = std::accumulate(products.begin(), products.end(), 0.0, 
		[](double s, Product p) {
			return s + p.getPrice();
		});
	this->ui.totalSum->setText(QString::number(total));
}
