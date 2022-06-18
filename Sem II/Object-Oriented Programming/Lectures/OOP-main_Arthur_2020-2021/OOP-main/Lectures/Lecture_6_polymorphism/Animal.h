#pragma once

#include <string>

namespace polymorphism {
    class Animal {
    protected:
        std::string colour;
        double weight;

    public:
        Animal(std::string _colour, double _weight);

        //~Animal();
        virtual ~Animal();

        std::string getColour() const;

        double getWeight() const;

        //std::string toString() const;

        virtual std::string toString() const;    // allows polymorphism
    };
}