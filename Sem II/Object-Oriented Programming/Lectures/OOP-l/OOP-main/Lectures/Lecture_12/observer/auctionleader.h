#pragma once
#include <QWidget>
#include "ui_auctionleader.h"
#include "Auctioneer.h"

class AuctionLeader : public QWidget 
{
	Q_OBJECT

private:
	Auctioneer& auct;

public:
	AuctionLeader(Auctioneer& c, QWidget * parent = Q_NULLPTR);
	~AuctionLeader();

private:
	Ui::AuctionLeader ui;

	void populateList();
	void setCurrent();
};
