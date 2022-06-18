#pragma once

#include <string>

namespace VectorThree {

    class Vector2D {
    private:
        double xCoordinate;
        double yCoordinate;

        static int numberOfInstances;

    public:
        // static data member
        //static int numberOfInstances;
        // static function
        static int getNumberOfInstances();

        // default constructor
        Vector2D(double x = 0, double y = 0);

        // copy constructor
        Vector2D(const Vector2D &v);

        // destructor
        ~Vector2D();

        double getXCoordinate() { return this->xCoordinate; }

        double getXCoordinate() const { return this->xCoordinate; }

        double getYCoordinate() { return this->yCoordinate; }

        /*
            Add the given 2D vector to the current 2D vector.
            Input: v - Vector2D
            Output: v is added to the current 2D vector.
        */
        void add(const Vector2D &v);

        /*
            Subtract the given 2D vector from the current 2D vector.
            Input: v - Vector2D
            Output: v is subtracted from the current 2D vector.
        */
        void subtract(Vector2D v);

        /*
            Rotates the current 2D vector.
            Input: angle - real value
            Output: the current 2D vector is rotated with the given angle.
        */
        void rotate(double angle);

        std::string toString();

        /*
            Multiplies the current 2D vector with a scalar value.
            Input: scalarValue - real number
            Output: the current 2D vector is multiplied by the given value.
        */
        void multiplyByScalar(double scalarValue);

        // operator overloading
        /*
            Overloading the + operator to add 2 2D vectors.
            Input: v - Vector2D
            Output: a 2D vector representing the sum of the current 2D vector and the parameter v.
        */
        Vector2D operator+(const Vector2D &v);

        /*
            Overloading the * operator to multiply a 2D vector with a scalar value.
            Input: scalarValue - double
            Output: a 2D vector representing the product of the current 2D vector and the given scalar value.
        */
        Vector2D operator*(double scalarValue);

        // assignment operator
        Vector2D &operator=(const Vector2D &v);

        // friend function
        friend void printVectorData(const Vector2D &v);

        // friend class
        friend class Graphics;
    };

// non-member function
    Vector2D operator*(double scalarValue, const Vector2D &v);


    class Graphics {
    private:
        Vector2D graphicElements[20];
        int noOfElements;

    public:
        Graphics(Vector2D elems[], int size);

        void printAllYCoordinates();
    };
}