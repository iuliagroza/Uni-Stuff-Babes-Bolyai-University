#include "GeneRepository.h"
#include <fstream>

namespace genes {

    GeneRepository::GeneRepository(const std::string &filename) : fileName{filename} {
        this->loadFromFile();
    }

    GeneRepository::~GeneRepository() {
    }

    void GeneRepository::loadFromFile() {
        std::ifstream f{this->fileName};
        if (!f.is_open())
            return;

        std::string organismName, geneName, sequence;
        while (f >> geneName) {
            Gene g{geneName, organismName, sequence};
            this->genes.push_back(g);
        }
    }
}