#include "BeverageMachine.h"
#include <iostream>

using namespace std;

Beverage::Beverage(): description{""}
{
}

Beverage::Beverage(const std::string & desc): description {desc}
{
}

Beverage::~Beverage()
{
}

void Beverage::print()
{
	cout << this->description << " " << this->price();
}

Coffee::Coffee(): Beverage{"Coffee"}
{
}

double Coffee::price()
{
	return 4.5;
}

Tea::Tea(): Beverage{"Tea"}
{
}

double Tea::price()
{
	return 3.5;
}

BeverageWithMilk::BeverageWithMilk(Beverage * b, int milkC) : beverage{ b }, milkCount{milkC}
{
}

void BeverageWithMilk::print()
{
	if (this->beverage == nullptr)
		return;
	this->beverage->print();
	cout << "; ";
	if (this->milkCount > 0)
		cout << " + " << this->milkCount << " portion(s) of milk." << "\t";
	cout << "Total price: " << this->price();
}

double BeverageWithMilk::price()
{
	if (this->beverage == nullptr)
		return 0;
	return this->beverage->price() + 0.5 * this->milkCount;
}

void BeverageMachine::prepare(const std::string& beverageType, int milkCount)
{
	if (beverageType != "Coffee" && beverageType != "Tea")
		return;
	Beverage* bev = nullptr;	
	//unique_ptr<Beverage> bev{};
	if (beverageType == "Coffee")
		bev = new Coffee{};		
		//bev = make_unique<Coffee>();
	else
		bev = new Tea{};		
		//bev = make_unique<Tea>();
	BeverageWithMilk withMilk{ bev, milkCount }; 
	//BeverageWithMilk withMilk{ bev.get(), milkCount };
	withMilk.print();
	cout << endl;

	delete bev;	// no need for this if using unique_ptr
}
