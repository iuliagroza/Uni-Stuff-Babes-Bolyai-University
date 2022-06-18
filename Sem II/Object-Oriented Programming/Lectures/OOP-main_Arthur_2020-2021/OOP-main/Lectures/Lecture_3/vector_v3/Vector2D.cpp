#include "Vector2D.h"
#include <cmath>
#include <sstream>
#include <iostream>

namespace VectorThree {

// initialize the static member
    int Vector2D::numberOfInstances = 0;

    int Vector2D::getNumberOfInstances() {
        return numberOfInstances;
    }

    Vector2D::Vector2D(double x, double y) : xCoordinate(x), yCoordinate(y) {
        numberOfInstances++;
    }

    Vector2D::Vector2D(const Vector2D &v) {
        this->xCoordinate = v.xCoordinate;
        this->yCoordinate = v.yCoordinate;

        numberOfInstances++;
    }

    Vector2D::~Vector2D() {
        //std::cout << "Destructor";

        //numberOfInstances--;
    }

    void Vector2D::add(const Vector2D &v) {
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

    std::string Vector2D::toString() {
        std::stringstream txt;
        txt << "X and Y coordinates: (" << this->xCoordinate << "," << this->yCoordinate << ")" << std::endl;
        return txt.str();
    }

    Vector2D Vector2D::operator+(const Vector2D &v) {
        Vector2D res(this->xCoordinate, this->yCoordinate);
        res.add(v);
        return res;
    }

    Vector2D Vector2D::operator*(double scalarValue) {
        Vector2D res(*this);
        res.multiplyByScalar(scalarValue);
        return res;
    }

    Vector2D &Vector2D::operator=(const Vector2D &v) {
        this->xCoordinate = v.xCoordinate;
        this->yCoordinate = v.yCoordinate;
        return *this;
    }


// non-member function
    Vector2D operator*(double scalarValue, const Vector2D &v) {
        Vector2D res(v);
        res.multiplyByScalar(scalarValue);
        return res;
    }

// friend function definition
    void printVectorData(const Vector2D &v) {
        std::cout << "X and Y coordinates: (" << v.xCoordinate << "," << v.yCoordinate << ")" << std::endl;
    }


// friend class
    Graphics::Graphics(Vector2D elems[], int size) {
        this->noOfElements = size;
        for (int i = 0; i < size; i++)
            this->graphicElements[i] = elems[i];
    }

    void Graphics::printAllYCoordinates() {
        for (int i = 0; i < this->noOfElements; i++)
            std::cout << "Y coordinate: " << i << ": " << this->graphicElements[i].yCoordinate << std::endl;
    }
}