#pragma once

namespace VectorTwo {

    class Vector2D {
    private:
        double xCoordinate;
        double yCoordinate;

    public:
        // default constructor
//         Vector2D();
        Vector2D(double x = 0, double y = 0);


        // constructor with parameters
        //Vector2D(double x, double y);

        // copy constructor
        Vector2D(const Vector2D &v);

        // destructor
        ~Vector2D();

        // we can have 2 functions with the same name and parameter list, if one is const
        double getXCoordinate() { return this->xCoordinate; }

        double getXCoordinate() const { return this->xCoordinate; }


        double getYCoordinate() const { return this->yCoordinate; }

        /*
            Add the given 2D vector to the current 2D vector.
            Input: v - Vector2D
            Output: v is added to the current 2D vector.
        */
        void add(Vector2D v);

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

        /*
            Multiplies the current 2D vector with a scalar value.
            Input: scalarValue - real number
            Output: the current 2D vector is multiplied by the given value.
        */
        void multiplyByScalar(double scalarValue);
    };
}