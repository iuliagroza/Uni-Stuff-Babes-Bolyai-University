#include "Zoo.h"

namespace abstract_base_class {
    std::vector<Animal *> Zoo::filterBy(const Filter &filter) {
        std::vector<Animal *> result;

        for (auto a : this->animals) {
            if (filter.include(*a))
                result.push_back(a);
        }

        return result;
    }
}