#include "ListViewWidget.h"

ListViewWidget::ListViewWidget(ProductsModel* model, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.productsListView->setModel(model);

	QObject::connect(ui.addButton, &QPushButton::clicked, this, [&]() {
		Product p{ "Default", 100 };
		model->addProduct(p);
		});

	QObject::connect(ui.clearButton, &QPushButton::clicked, this, [&]() {
		model->clearData();
		});
}

ListViewWidget::~ListViewWidget()
{
}
