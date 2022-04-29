#include "Vector2D.h"
#include <iostream>
#include <Windows.h>

#define PI 3.14159265
#include<cmath>

int main()
{
	system("color f4");

	{
		Vector2D v{1, 2};
	}

	Vector2D v1{};	// default constructor called
	
	//Vector2D v3();	// !!! This is a function definition
	//v3.add(v2);

	Vector2D v3{ 2, 3 };	// constructor with parameters called
	const Vector2D a = v3;
	//a.add(v3);	// error - a is const and the function add is not const

	Vector2D arrayOfVectors[5];	// default constructor is called 5 times

	Vector2D arrayOfVectorsInitialized[3] = { {}, {2, 3}, Vector2D{-1, 1} }; // first default constructor, then 2 times the constructor with parameters

	Vector2D v4{v3};	// copy constructor called
	Vector2D v5 = v4;	// copy constructor called

	// dynamic allocation
	Vector2D* v6 = new Vector2D{};		// default constructor
	Vector2D* v7 = new Vector2D{1, 7};	// constructor with parameters
	Vector2D* v8 = new Vector2D{ *v7 };	// copy constructor
	Vector2D* arrayOfVectorsDynamic = new Vector2D[3];	// default constructor
	v6->add(*v7);	// is any constructor called in this case?
	
	// deallocation
	delete v6;
	delete v7;
	delete v8;
	delete[] arrayOfVectorsDynamic;

	system("pause");
	return 0;
}