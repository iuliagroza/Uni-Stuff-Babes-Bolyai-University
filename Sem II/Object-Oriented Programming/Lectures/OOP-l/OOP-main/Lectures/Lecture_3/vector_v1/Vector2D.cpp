#include "Vector2D.h"
#include <cmath>

namespace VectorOne {

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