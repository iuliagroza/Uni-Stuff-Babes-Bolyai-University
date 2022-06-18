#include <iostream>
#include "Spaceship.h"
#include "SpaceshipValidator.h"

using namespace std;
using namespace Lecture_7_exceptions;

class MyException : public std::exception
{
private:
	string message;

public:
	MyException(const string& s) : message{ s } {}

	const char* what() const throw() override {
		return this->message.c_str();
	}
};


void f()
{
	throw MyException{ "exception\n" };
}

void handle()
{
	try
	{
		f();
	}
	catch (std::exception e)
	{
		cout << e.what();
	}
}


void exceptionHandling(bool throwEx) 
{
	try 
	{
		cout << "Code before the exception" << endl;
		if (throwEx) 
		{
			cout << "Throw exception" << endl;
			throw 12;
		}
		cout << "Code after the exception" << endl;
	}
	catch (int) 
	{
		cout << "Error handling code " << endl;
	}

	cout << "Done." << endl;
}

// -----------------------------------------------------------------------------------------------------------------------------

void exceptionExecutionFlowFct1()
{
	cout << "Function 1: code before exception." << endl;
	throw string{"exception"};
}

void exceptionExecutionFlowFct2()
{
	try
	{
		exceptionExecutionFlowFct1();
	}
	catch (int&) // trying to catch a type different than the type that was thrown
	{
		cout << "Tried to catch an integer." << endl;
	}
	catch (string&)
	{
		cout << "Exception in function exceptionExecutionFlowFct1 is being handled." << endl;
		//throw; // re-throw exception - cannot be handled by the same try-catch block
	}
	catch (...)
	{
		cout << "Caught exception." << endl;
	}
}

// -----------------------------------------------------------------------------------------------------------------------------

class A
{
private:
	int x;

public:
	A() : x{ 0 } {}
	virtual void f() {}
};

class B : public A 
{
	void f() override {};
};

void multipleHandlers(string type)
{
	try
	{
		if (type == "A")
			throw A{};
		else 
		if (type == "B")
			throw B{};
		else
			throw 20;
	}
	catch (A& a)
	{
		cout << "Caught object of type A." << endl;
		a.f();
	}
	catch (B&)
	{
		cout << "Caught object of type B." << endl;
	}
	catch (...)
	{
		cout << "Caught object of unknown type." << endl;
	}
}

// -----------------------------------------------------------------------------------------------------------------------------
// user defined exceptions

void testSpaceshipException()
{
	Spaceship deathStar{ "Death Star", "darth Vader", "dreadnought" };
	try
	{
		SpaceshipValidator::validate(deathStar);
	}
	catch (ValidationException& ex)
	//catch (ValidationExceptionInherited& ex)
	//catch (exception& ex)
	{
		cout << ex.getMessage() << endl;
		//cout << ex.what() << endl;
	}
}

// -----------------------------------------------------------------------------------------------------------------------------

//int main()
//{
//	/*exceptionHandling(true);
//	exceptionHandling(false);
//
//	exceptionExecutionFlowFct2();
//*/
//
//	multipleHandlers("A");
//	multipleHandlers("B");
//	multipleHandlers("");
//
//	testSpaceshipException();
//
//	return 0;
//}