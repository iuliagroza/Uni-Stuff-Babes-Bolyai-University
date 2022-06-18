#include "GeneRepository.h"
#include <fstream>
#include <string>
#include <sstream>

namespace genes_custom_model {
    GeneRepository::GeneRepository(const std::string &filename) : fileName{filename} {
        this->loadFromFile();
    }

    GeneRepository::~GeneRepository() {
    }

    void GeneRepository::addGene(const Gene &g) {
        this->genes.push_back(g);
    }

    void GeneRepository::updateGene(int index, const Gene &g) {
        if (index < 0 || index >= this->genes.size())
            return;

        this->genes.erase(this->genes.begin() + index);
        this->genes.insert(this->genes.begin() + index, g);

        this->saveToFile();
    }

    void GeneRepository::loadFromFile() {
        std::ifstream f{this->fileName};
        if (!f.is_open())
            return;

        Gene g;
        while (f >> g) {
            this->genes.push_back(g);
        }
    }

    void GeneRepository::saveToFile() {
        std::ofstream f{this->fileName};
        if (!f.is_open())
            return;

        for (auto g : this->genes)
            f << g.toString();
    }
}