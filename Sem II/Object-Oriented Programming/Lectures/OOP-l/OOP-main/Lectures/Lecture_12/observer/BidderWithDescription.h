#pragma once
#include <QWidget>
#include "ui_bidderwithdescription.h"
#include "Observer.h"
#include "Auctioneer.h"

class BidderWithDescription : public QWidget, public Observer 
{
	Q_OBJECT

public:
	Auctioneer& auct;
public:
	BidderWithDescription(Auctioneer& c, QWidget * parent = Q_NULLPTR);
	~BidderWithDescription();

	// implements the update method of the observer - it will update the description of the current house and the price
	void update() override;

private:
	Ui::BidderWithDescription ui;

	void connectSignals();
};
