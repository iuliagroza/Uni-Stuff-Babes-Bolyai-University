#pragma once

#include <QWidget>
#include "ui_TableViewWidget.h"
#include "ProductsModel.h"

class TableViewWidget : public QWidget
{
	Q_OBJECT

public:
	TableViewWidget(ProductsModel* model, QWidget *parent = Q_NULLPTR);
	~TableViewWidget();

private:
	Ui::TableViewWidget ui;
};
