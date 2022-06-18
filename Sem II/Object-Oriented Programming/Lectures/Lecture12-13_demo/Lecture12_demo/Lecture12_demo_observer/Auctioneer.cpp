#include "Auctioneer.h"

Auctioneer::Auctioneer()
{
	this->current = 0;
}


Auctioneer::~Auctioneer()
{
}

void Auctioneer::addCastle(std::string desc, std::string picture, std::string loc, int startPr, int lastBiddingPr)
{
	Castle c{ desc, picture, loc, startPr, lastBiddingPr };
	this->castles.push_back(c);
}

void Auctioneer::changePrice(int castleIdx, int sumToAdd)
{
	if (castleIdx < 0 || castleIdx >= this->castles.size())
		return;
	Castle& currentCastle = this->castles[castleIdx];
	currentCastle.setLastBidPrice(currentCastle.getLastBidPrice() + sumToAdd);

	// notify all the observers that the price was changed
	this->notify();
}

void Auctioneer::setCurrent(int c)
{
	this->current = c;

	// notify that the castle was changed
	this->notify();
}
