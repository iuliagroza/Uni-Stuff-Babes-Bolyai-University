#pragma once
#include <QWidget>
#include "ui_bidderwithphoto.h"
#include "Observer.h"
#include "Auctioneer.h"

class BidderWithPhoto : public QWidget, public Observer
{
	Q_OBJECT

private:
	Auctioneer& auct;
public:
	BidderWithPhoto(Auctioneer& c, QWidget * parent = Q_NULLPTR);
	~BidderWithPhoto();

	// implements the update method of the observer - it will update the description of the current house and the price
	void update() override;

private:
	Ui::BidderWithPhoto ui;
};
