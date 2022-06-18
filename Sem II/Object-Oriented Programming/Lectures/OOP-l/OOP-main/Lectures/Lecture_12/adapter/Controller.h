#pragma once
#include <vector>
#include "Castle.h"
#include "PaymentService.h"
#include <memory>

class Controller
{
private:
	std::vector<Castle> castles;
	int current;

public:
	Controller();
	~Controller();

	void addCastle(std::string desc, std::string picture, std::string loc, double startPr, double lastBiddingPr);

	std::vector<Castle> getCastles() { return this->castles; }

	int getCurrent() const { return this->current; }
	void setCurrent(int c);

	std::string buy(std::unique_ptr<PaymentService> service);
};

