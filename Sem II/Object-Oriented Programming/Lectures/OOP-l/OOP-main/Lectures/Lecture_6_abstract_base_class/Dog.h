#pragma once

#include "Animal.h"

namespace abstract_base_class {
    class Dog : public Animal {
    private:
        std::string breed;
        double furLength;

    public:
        Dog(std::string _colour, double _weight, std::string _breed, double _furLength);

        ~Dog();

        std::string getBreed() const;

        double getFurLength() const;

        std::string toString() const;

        void speak() const override;
    };
}
