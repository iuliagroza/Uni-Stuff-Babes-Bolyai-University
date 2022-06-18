#include "DialogGenesView.h"
#include <QStringListModel>
#include <ctime>
#include <QMessageBox>

DialogGenesView::DialogGenesView(GeneRepository& r, QWidget* parent) : QDialog{ parent }, repo{ r }
{
	ui.setupUi(this);
	QFont font("Courier", 20, 10, true);
	this->ui.listView->setFont(font);

	// build a predefined model: QStringListModel
	QStringListModel* model = new QStringListModel{};
	QStringList list;
	for (auto g : this->repo.getGenes())
		list.append(QString::fromStdString(g.getName()));

	model->setStringList(list);
	ui.listView->setModel(model);
}


DialogGenesView::~DialogGenesView()
{
}
