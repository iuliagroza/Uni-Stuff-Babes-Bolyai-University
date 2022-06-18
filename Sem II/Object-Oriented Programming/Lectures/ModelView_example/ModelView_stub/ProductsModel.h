#pragma once
#include <QAbstractTableModel>
#include "ShoppingBasket.h"

class ProductsModel : public QAbstractTableModel
{
private:
	ShoppingBasket& basket;

public:
	ProductsModel(ShoppingBasket& basket);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	void addProduct(const Product& p);
	void clearData();
};

