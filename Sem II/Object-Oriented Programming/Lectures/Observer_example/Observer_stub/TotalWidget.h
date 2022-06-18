#pragma once

#include <QWidget>
#include "ui_TotalWidget.h"
#include "Observer.h"
#include "ShoppingBasket.h"

class TotalWidget : public QWidget, public Observer
{
	Q_OBJECT

public:
	TotalWidget(ShoppingBasket& basket, QWidget *parent = Q_NULLPTR);
	~TotalWidget();

	void update() override;

private:
	Ui::TotalWidget ui;
	ShoppingBasket& basket;
};
