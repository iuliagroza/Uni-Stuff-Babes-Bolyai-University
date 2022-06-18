#pragma once
namespace VectorOne {

    class Vector2D {

    public:
        double xCoordinate;
        double yCoordinate;

    public:
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