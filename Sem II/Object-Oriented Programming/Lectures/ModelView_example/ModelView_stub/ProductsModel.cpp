#include "ProductsModel.h"
#include <QFont>
#include <QBrush>

ProductsModel::ProductsModel(ShoppingBasket& basket): basket{basket}
{
}

int ProductsModel::rowCount(const QModelIndex& parent) const
{
	return this->basket.getSize();
}

int ProductsModel::columnCount(const QModelIndex& parent) const
{
	return 2;
}

QVariant ProductsModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	Product p = this->basket.getAll()[row];

	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(p.getName());
		case 1:
			return QString::number(p.getPrice());
		default:
			break;
		}
	}

	if (role == Qt::FontRole)
	{
		QFont font{ "Verdana", 15 };
		return font;
	}

	if (role == Qt::BackgroundRole)
	{
		if (row % 2 == 1)
		{
			QBrush brush{ QColor{220, 220, 220} };
			return brush;
		}
	}

	if (role == Qt::UserRole)
		if (column == 1)
			return p.getPrice();

	return QVariant();
}

QVariant ProductsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal)
	{
		if (role == Qt::DisplayRole)
		{
			switch (section)
			{
			case 0:
				return QString{ "Name" };
			case 1:
				return QString{ "Price" };
			default:
				break;
			}
		}
	}

	return QVariant();
}

void ProductsModel::addProduct(const Product& p)
{
	int n = this->basket.getSize();

	this->beginInsertRows(QModelIndex{}, n, n);

	this->basket.addProduct(p);

	this->endInsertRows();
}

void ProductsModel::clearData()
{
	this->beginResetModel();

	this->basket.clear();

	this->endResetModel();
}
