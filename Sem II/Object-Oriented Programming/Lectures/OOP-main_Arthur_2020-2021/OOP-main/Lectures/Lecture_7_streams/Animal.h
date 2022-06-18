#pragma once

#include <string>
#include <iostream>

namespace Lecture_7_streams {
    class Animal {
    protected:
        std::string colour;
        double weight;

    public:
        Animal() : colour{""}, weight{0} {}

        Animal(std::string _colour, double _weight);

        ~Animal();
        //virtual ~Animal();

        std::string getColour() const;

        double getWeight() const;

        //std::string toString() const;

        virtual std::string toString() const;    // allows polymorphism

        friend std::istream &operator>>(std::istream &stream, Animal &a);

        friend std::ostream &operator<<(std::ostream &stream, const Animal &a);
    };
}
