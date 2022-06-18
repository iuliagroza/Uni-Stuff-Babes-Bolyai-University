#include "BidderWithDescription.h"

BidderWithDescription::BidderWithDescription(Auctioneer& c, QWidget * parent) : QWidget(parent), auct{ c }
{
	ui.setupUi(this);

	// add this (which is an observer) to the list of observers of the Auctioneer
	this->auct.addObserver(this);

	this->connectSignals();
}

BidderWithDescription::~BidderWithDescription() 
{
	// remove the observer when it is destroyed
	this->auct.removeObserver(this);
}

void BidderWithDescription::update()
{
	std::vector<Castle> castles = this->auct.getCastles();
	int current = this->auct.getCurrent();
	if (current < 0 || current > castles.size())
		return;

	Castle currentCastle = castles[current];

	// get description
	this->ui.labelDescription->setText(QString::fromStdString(currentCastle.getDescription() + ", " + currentCastle.getLocation()));

	// get last bidding price
	this->ui.labelPrice->setText(QString{ "Last bid: " } +QString::number(currentCastle.getLastBidPrice()) + QString{ " thousand pounds" });
}

void BidderWithDescription::connectSignals()
{
	QObject::connect(this->ui.add100Button, &QPushButton::clicked, [&]() 
	{
		this->auct.changePrice(this->auct.getCurrent(), 100);
	});

	QObject::connect(this->ui.add1000Button, &QPushButton::clicked, [&]()
	{
		this->auct.changePrice(this->auct.getCurrent(), 1000);
	});
}
