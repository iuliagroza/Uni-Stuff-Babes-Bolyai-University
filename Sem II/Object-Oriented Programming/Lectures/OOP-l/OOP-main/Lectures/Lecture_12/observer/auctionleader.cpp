#include "auctionleader.h"

AuctionLeader::AuctionLeader(Auctioneer& c, QWidget * parent) : QWidget(parent), auct{ c }
{
	ui.setupUi(this);
	this->populateList();

	// connect slot for "Start" button
	QObject::connect(this->ui.startButton, &QPushButton::clicked, [&]()
	{
		this->setCurrent();
	});
}

AuctionLeader::~AuctionLeader() 
{	
}

void AuctionLeader::populateList()
{
	// clear the list, if there are elements in it
	if (this->ui.housesListWidget->count() > 0)
		this->ui.housesListWidget->clear();

	for (auto c : this->auct.getCastles())
	{
		QString itemInList = QString::fromStdString(c.getDescription());
		QListWidgetItem *item = new QListWidgetItem(itemInList);
		QFont font("Courier", 20, 10, true);
		item->setFont(font);
		this->ui.housesListWidget->addItem(item);
	}

	// set the selection on the first item in the list
	if (this->ui.housesListWidget->count() > 0)
		this->ui.housesListWidget->setCurrentRow(0);

}

void AuctionLeader::setCurrent()
{
	if (this->ui.housesListWidget->count() == 0)
		return;

	// get selected index
	QModelIndexList index = this->ui.housesListWidget->selectionModel()->selectedIndexes();
	if (index.size() == 0)
	{
		return;
	}

	int idx = index.at(0).row();
	this->auct.setCurrent(idx);
}