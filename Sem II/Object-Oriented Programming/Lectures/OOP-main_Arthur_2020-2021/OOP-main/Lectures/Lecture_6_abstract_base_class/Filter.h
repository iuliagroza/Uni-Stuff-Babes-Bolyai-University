#pragma once

#include "Animal.h"
#include <string>

namespace abstract_base_class {
    class Filter {
    public:
        virtual bool include(const Animal &a) const = 0;

        virtual ~Filter() {};
    };

    class FilterWeightLessThan : public Filter {
    private:
        int weight;

    public:
        FilterWeightLessThan(int w) : weight(w) {}

        bool include(const Animal &a) const override { return a.getWeight() < this->weight; }
    };

    class FilterColor : public Filter {
    private:
        std::string colour;

    public:
        FilterColor(std::string c) : colour(c) {}

        bool include(const Animal &a) const override { return a.getColour() == this->colour; }
    };
}