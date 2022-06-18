#include "BidderWithPhoto.h"

BidderWithPhoto::BidderWithPhoto(Auctioneer& c, QWidget * parent) : QWidget(parent), auct{ c }
{
	ui.setupUi(this);
	this->auct.addObserver(this);

	// handle signal from the button
	QObject::connect(this->ui.add2000Button, &QPushButton::clicked, [&]()
	{
		this->auct.changePrice(this->auct.getCurrent(), 2000);
	});
}

BidderWithPhoto::~BidderWithPhoto() 
{
	this->auct.removeObserver(this);
}

void BidderWithPhoto::update()
{
	std::vector<Castle> castles = this->auct.getCastles();
	int current = this->auct.getCurrent();
	if (current < 0 || current > castles.size())
		return;

	Castle currentCastle = castles[current];

	// set photo
	QPixmap pixmap(QString::fromStdString(currentCastle.getPhoto()));
	this->ui.photoLabel->setPixmap(pixmap);

	// get last bidding price
	this->ui.priceLabel->setText(QString{ "Last bid: " } +QString::number(currentCastle.getLastBidPrice()) + QString{ " thousand pounds" });
}
