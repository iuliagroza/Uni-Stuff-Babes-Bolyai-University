#include "Controller.h"

Controller::Controller()
{
	this->current = 0;
}


Controller::~Controller()
{
}

void Controller::addCastle(std::string desc, std::string picture, std::string loc, double startPr, double lastBiddingPr)
{
	Castle c{ desc, picture, loc, startPr, lastBiddingPr };
	this->castles.push_back(c);
}

void Controller::setCurrent(int c)
{
	this->current = c;
}

std::string Controller::buy(std::unique_ptr<PaymentService> service)
{
	if (service == nullptr)
		return "";
	if (this->current < 0 || this->current >= this->castles.size())
		return "";

	// get current castle
	Castle& c = this->castles[this->current];
	return service->pay(c.getStartPrice());
}
