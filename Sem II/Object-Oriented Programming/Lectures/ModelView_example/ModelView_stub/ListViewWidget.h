#pragma once

#include <QWidget>
#include "ui_ListViewWidget.h"
#include "ProductsModel.h"

class ListViewWidget : public QWidget
{
	Q_OBJECT

public:
	ListViewWidget(ProductsModel* model, QWidget *parent = Q_NULLPTR);
	~ListViewWidget();

private:
	Ui::ListViewWidget ui;
};
