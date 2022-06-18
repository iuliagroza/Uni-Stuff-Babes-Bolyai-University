#pragma once
#include <vector>
#include "Castle.h"
#include "Observer.h"

/*
	This will be changed each time someone makes a new bid for a house.
	Therefore, it must extend Observable and notify all its observers when something changed.
*/
class Auctioneer: public Observable
{
private:
	std::vector<Castle> castles;
	int current;

public:
	Auctioneer();
	~Auctioneer();

	void addCastle(std::string desc, std::string picture, std::string loc, int startPr, int lastBiddingPr);

	std::vector<Castle> getCastles() { return this->castles; }

	int getCurrent() const { return this->current; }
	
	// The following two functions modify the necessary data and notify all the observers of the Auctioneer.
	// changes the price for the castle with the given index
	void changePrice(int castleIdx, int sumToAdd);
	void setCurrent(int c);
};

