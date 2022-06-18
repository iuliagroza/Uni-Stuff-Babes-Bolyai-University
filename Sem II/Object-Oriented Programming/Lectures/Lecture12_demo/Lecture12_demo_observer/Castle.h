#pragma once
#include <string>

class Castle
{
private:
	std::string description;
	std::string photo;
	std::string location;
	int startPrice;
	int lastBidPrice;

public:
	Castle(std::string desc, std::string picture, std::string loc, int startPr, int lastBiddingPr) : description{ desc }, photo{ picture }, location{ loc }, startPrice{ startPr }, lastBidPrice{ lastBiddingPr } {}
	std::string getDescription() const { return this->description; }
	std::string getPhoto() const { return this->photo; }
	std::string getLocation() const { return this->location; }
	int getStartPrice() const { return this->startPrice; }
	int getLastBidPrice() const { return this->lastBidPrice; }

	void setLastBidPrice(int pr) { this->lastBidPrice = pr; }
};
