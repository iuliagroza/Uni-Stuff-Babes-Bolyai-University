#pragma once

#include <string>
#include <memory>

class Beverage
{
private:
	std::string description;

public:
	Beverage();
	Beverage(const std::string& desc);
	virtual double price() = 0;
	virtual void print();
	virtual ~Beverage();
};

class Coffee : public Beverage
{
public:
	Coffee();
	double price() override;
};

class Tea : public Beverage
{
public:
	Tea();
	double price() override;
};

class BeverageWithMilk : public Beverage
{
private:
	Beverage* beverage;
	int milkCount;

public:
	BeverageWithMilk(Beverage* b, int milkC);
	void print() override;
	double price() override;
};

class BeverageMachine
{
public:
	static void prepare(const std::string& beverageType, int milkCount);
};

