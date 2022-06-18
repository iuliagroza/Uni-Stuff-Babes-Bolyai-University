#pragma once

#include <vector>
#include "Filter.h"

namespace abstract_base_class {
    class Zoo {
    private:
        std::vector<Animal *> animals;

    public:
        Zoo(const std::vector<Animal *> a) : animals(a) {}

        std::vector<Animal *> filterBy(const Filter &filter);
    };
}
