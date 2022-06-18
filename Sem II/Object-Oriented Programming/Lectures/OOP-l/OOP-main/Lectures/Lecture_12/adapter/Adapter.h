#pragma once
#include "PaymentService.h"

// example of a class Adapter
class AdapterClass : public PaymentService, public GoCardlessUK
{
private:
	double conversionEuroToPoundsRate;

public:
	AdapterClass(double conversionRate) : conversionEuroToPoundsRate{ conversionRate } {}

	std::string pay(double sum) override
	{
		double sumPounds = this->conversionEuroToPoundsRate * sum;
		this->sendPayment(sumPounds); // make the payment

		std::stringstream s;
		s << "Paid " << sumPounds << " million pounds using GoCardlessUK.\n";
		return s.str();
	}
};

// example of object adapter
class AdapterObject : public PaymentService
{
	private:
		double conversionEuroToPoundsRate;
		GoCardlessUK& goCardlessUK;

public:
	AdapterObject(double conversionRate, GoCardlessUK& goCardless) : conversionEuroToPoundsRate{ conversionRate }, goCardlessUK{ goCardless } {}

	std::string pay(double sum) override
	{
		double sumPounds = this->conversionEuroToPoundsRate * sum;
		goCardlessUK.sendPayment(sumPounds); // make the payment

		std::stringstream s;
		s << "Paid " << sumPounds << " million pounds using GoCardlessUK.\n";
		return s.str();
	}
};