#include <Windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <assert.h>
#include <deque>
#include <string>
#include "BeverageMachine.h"
#include <crtdbg.h>

using namespace std;

template <typename T>
class Stack
{
private:
	std::vector<T> stack;
	int capacity;

public:
	Stack(int cap = 10) : capacity{ cap } {}

	int getMaxCapacity()
	{
		return capacity;
	}

	Stack operator+(const T& elem)
	{
		if (this->stack.size() < this->capacity)
		{
			stack.push_back(elem);
			return *this;
		}
		else
			throw std::exception{ "Stack is full!" };
	}

	T pop()
	{
		T e = stack.back();
		stack.pop_back();
		return e;
	}
};

void testStack()
{
	Stack<std::string> s{ 2 };
	assert(s.getMaxCapacity() == 2);
	try {
		s = s + "examination";
		s = s + "oop";
		s = s + "test";
	}
	catch (std::exception& e) {
		assert(strcmp(e.what(), "Stack is full!") == 0);
	}
	assert(s.pop() == "oop");
	assert(s.pop() == "examination");
}


// ------------------------------------------------------------------------------------------------------------------------------------------------------

class Activity
{
private:
	std::string description;
	std::string time;

public:
	Activity(const std::string& d, const std::string& t) : description{ d }, time{ t } {}

	friend std::ostream& operator<<(std::ostream& os, const Activity& a)
	{
		os << "Activity " << a.description << " will take place at " << a.time << ".";
		return os;
	}
};


template <typename T>
class ToDo
{
private:
	std::deque<T> list;

public:
	void operator+=(const Activity& a)
	{
		this->list.push_front(a);
	}

	typename std::deque<T>::iterator begin()
	{
		return this->list.begin();
	}

	typename std::deque<T>::iterator end()
	{
		return this->list.end();
	}

	void reversePrint(std::ostream& os)
	{
		for (auto i = this->list.size() - 1; i >= 0; i--)
			os << this->list[i] << "\n";
	}
};

void ToDoList()
{
	ToDo<Activity> todo{};
	Activity tiff{ "go to TIFF movie", "20:00" };
	todo += tiff;
	Activity project{ "present project assignment", "09.20" };
	todo += project;

	// iterates through the activities and prints them as follows:
	// Activity present project assignment will take place at 09.20.
	// Activity go to TIFF movie will take place at 20.00.
	for (auto a : todo)				
		std::cout << a << '\n';

	// Prints the activities as follows:
	// Activity go to TIFF movie will take place at 20.00.
	// Activity present project assignment will take place at 09.20.
	todo.reversePrint(std::cout);
}

// ******************************************************************************************************************************************************
class B {
public:
	B() { std::cout << "B{}"; }
	virtual void print() { std::cout << "B"; }
	virtual ~B() { std::cout << "~B()"; }
};

class D : public B {
public:
	D() { std::cout << "D{}"; }
	void print() { std::cout << "D"; }
	virtual ~D() { std::cout << "~D()"; }
};

// ******************************************************************************************************************************************************

class Person {
public:
	Person(int x = 9) { std::cout << "Person{}"; }
	virtual void print() = 0;
	virtual ~Person() { std::cout << "~Person()"; }
};

class Student : public Person {
public:
	Student() { std::cout << "Student{}"; }
	void print() { std::cout << "Student"; }
	virtual ~Student() { std::cout << "~Student()"; }
};

// ******************************************************************************************************************************************************

class E {
public:
	E() { cout << "E{} "; }
	virtual ~E() { cout << "~E() "; }
};

class DE : public E {
public:
	static int n;
	DE() { n++; }
};

int DE::n = 0;

int fct2(int x) {
	if (x < 0) {
		throw E{};
		cout << "number less than 0 ";
	}
	else if (x == 0) {
		throw DE{};
		cout << "number equal to 0 ";
	}
	return x % 10;
}

// ******************************************************************************************************************************************************

int main()
{
	// --------------------------------------------------------------------------------------------------------------------------------------------
	testStack();

	// --------------------------------------------------------------------------------------------------------------------------------------------
	ToDoList();

	//// --------------------------------------------------------------------------------------------------------------------------------------------

	//B* b[] = { new B{}, new D{} };
	//b[0]->print();					
	//b[1]->print();					
	//delete b[0];					
	//delete b[1];
	//std::cout << std::endl;

	//// --------------------------------------------------------------------------------------------------------------------------------------------
	//
	//std::cout << std::endl;
	////Person* p = new Person{};
	////delete p;
	//Person* s = new Student{};
	//s->print();
	//delete s;
	//std::cout << std::endl;

	//// --------------------------------------------------------------------------------------------------------------------------------------------

	//try
	//{
	//	int res = 0;
	//	//res = fct2(-5);		//res = fct2(-5);
	//	std::cout << DE::n;
	//	//res = fct2(0);		//res = fct2(0);
	//	std::cout << DE::n;
	//	res = fct2(25);
	//	std::cout << DE::n;
	//}
	//catch (E&) 
	//{
	//	std::cout << DE::n;
	//}
	//std::cout << std::endl;

	//// --------------------------------------------------------------------------------------------------------------------------------------------

	//std::deque<std::string> d;
	//d.push_back("A");
	//d.push_front("B");
	//d.push_back("C");
	//d.push_front("D");

	//auto itBegin = d.begin();
	//auto itEnd = d.end();
	//itBegin++;
	//itEnd--;

	//while (itBegin != itEnd)
	//{
	//	std::cout << *itBegin << " ";
	//	itBegin++;
	//}
	//std::cout << std::endl;

	//// --------------------------------------------------------------------------------------------------------------------------------------------

	// Beverage machine
	/*BeverageMachine::prepare("Tea", 0);
	BeverageMachine::prepare("Coffee", 1);
	BeverageMachine::prepare("Coffee", 2);*/

	// --------------------------------------------------------------------------------------------------------------------------------------------
	
	_CrtDumpMemoryLeaks();
	return 0;
}