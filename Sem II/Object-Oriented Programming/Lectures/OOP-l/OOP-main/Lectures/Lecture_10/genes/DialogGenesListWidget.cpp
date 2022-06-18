#include "DialogGenesListWidget.h"

DialogGenesListWidget::DialogGenesListWidget(GeneRepository& r, QWidget* parent) : QDialog{ parent }, repo{ r }
{
	ui.setupUi(this);

	this->populateList();
}


DialogGenesListWidget::~DialogGenesListWidget()
{
}

void DialogGenesListWidget::populateList()
{
	// clear the list, if there are elements in it
	if (ui.listWidget->count() > 0)
		this->ui.listWidget->clear();

	int i = 1;
	for (auto g : this->repo.getGenes())
	{
		QString itemInList = QString::fromStdString(g.getName());
		QFont font("Courier", 20, 10, true);
		this->ui.listWidget->setFont(font);
		this->ui.listWidget->addItem(QString::number(i) + " - " + itemInList);
		i++;
	}

	// set the selection on the first item in the list
	if (this->ui.listWidget->count() > 0)
		this->ui.listWidget->setCurrentRow(0);
}
