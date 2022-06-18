#pragma once
#include <string>
#include <vector>
#include "../../Lecture_9/genes/Gene.h"

namespace genes {

    class GeneRepository {
    private:
        std::vector<Gene> genes;
        std::string fileName;

    public:
        GeneRepository(const std::string &filename);

        ~GeneRepository();

        std::vector<Gene> getGenes() const { return this->genes; }

    private:
        void loadFromFile();
    };

}