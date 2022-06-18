#include "Vector2D.h"
#include <cmath>
#include <iostream>

namespace VectorTwo {

//Vector2D::Vector2D()
//{
//	this->xCoordinate = 0;
//	this->yCoordinate = 0;
//
//	std::cout << "Constructor called.";
//}

    Vector2D::Vector2D(double x, double y) {
        this->xCoordinate = x;
        this->yCoordinate = y;
    }

//Vector2D::Vector2D(double x, double y)
//{
//	this->xCoordinate = x;
//	this->yCoordinate = y;
//}

// constructor with parameters using member initialization
//Vector2D::Vector2D(double x, double y) : xCoordinate{ x }, yCoordinate{ y }
//{}

    Vector2D::Vector2D(const Vector2D &v) {
        this->xCoordinate = v.xCoordinate;
        this->yCoordinate = v.yCoordinate;
    }

    Vector2D::~Vector2D() {
        std::cout << "Destructor called for " << this->xCoordinate << ", " << this->yCoordinate << std::endl;
    }

    void Vector2D::add(Vector2D v) {
        this->xCoordinate += v.xCoordinate;
        this->yCoordinate += v.yCoordinate;
    }

    void Vector2D::subtract(Vector2D v) {
        this->xCoordinate -= v.xCoordinate;
        this->yCoordinate -= v.yCoordinate;
    }

    void Vector2D::rotate(double angle) {
        this->xCoordinate = this->xCoordinate * cos(angle) - this->yCoordinate * sin(angle);
        this->yCoordinate = this->xCoordinate * sin(angle) + this->yCoordinate * cos(angle);
    }

    void Vector2D::multiplyByScalar(double scalarValue) {
        this->xCoordinate *= scalarValue;
        this->yCoordinate *= scalarValue;
    }
}