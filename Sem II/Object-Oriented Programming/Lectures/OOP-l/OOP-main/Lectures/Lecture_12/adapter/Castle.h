#pragma once
#include <string>

class Castle
{
private:
	std::string description;
	std::string photo;
	std::string location;
	double startPrice;
	double lastBidPrice;

public:
	Castle(std::string desc, std::string picture, std::string loc, double startPr, double lastBiddingPr) : description{ desc }, photo{ picture }, location{ loc }, startPrice{ startPr }, lastBidPrice{ lastBiddingPr } {}
	std::string getDescription() const { return this->description; }
	std::string getPhoto() const { return this->photo; }
	std::string getLocation() const { return this->location; }
	double getStartPrice() const { return this->startPrice; }
	double getLastBidPrice() const { return this->lastBidPrice; }

	void setLastBidPrice(double pr) { this->lastBidPrice = pr; }
};
