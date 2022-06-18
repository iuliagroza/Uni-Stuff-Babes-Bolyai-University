#pragma once

#include "Animal.h"

namespace abstract_base_class {
    class Penguin : public Animal {
    private:
        std::string type;

    public:
        Penguin(std::string _colour, double _weight, std::string _type);

        ~Penguin();

        std::string getType() const;

        std::string toString() const override;

        void speak() const override;
    };
}
