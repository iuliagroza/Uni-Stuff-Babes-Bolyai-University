#pragma once
#include <string>
#include <sstream>

class PaymentService
{
public:
	virtual std::string pay(double sum) = 0;
	virtual ~PaymentService() {}
};

class PayPal : public PaymentService
{
	std::string pay(double sum) override
	{
		std::stringstream s;
		s << "Paid " << sum << " million euro using PayPal.\n";
		return s.str();
	}
};

class Skrill: public PaymentService
{
	std::string pay(double sum) override
	{
		std::stringstream s;
		s << "Paid " << sum << " million euro using Skrill.\n";
		return s.str();
	}
};

class GoCardlessUK
{
public:
	void sendPayment(double sumInPounds)
	{
		// send a payment
	}
};