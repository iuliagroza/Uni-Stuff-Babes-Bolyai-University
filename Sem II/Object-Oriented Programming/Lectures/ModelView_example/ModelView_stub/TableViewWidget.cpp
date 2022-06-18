#include "TableViewWidget.h"
#include <QSortFilterProxyModel>

TableViewWidget::TableViewWidget(ProductsModel* model, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//ui.productsTableView->setModel(model);

	QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel{};
	proxyModel->setSourceModel(model);
	proxyModel->setSortRole(Qt::UserRole);
	ui.productsTableView->setModel(proxyModel);
	ui.productsTableView->setSortingEnabled(true);

	QObject::connect(ui.addButton, &QPushButton::clicked, this, [&]() {
		Product p{ "Default", 100 };
		model->addProduct(p);
		});

	QObject::connect(ui.clearButton, &QPushButton::clicked, this, [&]() {
		model->clearData();
		});
}

TableViewWidget::~TableViewWidget()
{
}
