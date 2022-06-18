#pragma once
#include <string>
#include <vector>
#include "Gene.h"

class GeneRepository
{
private:
	std::vector<Gene> genes;
	std::string fileName;

public:
	GeneRepository(const std::string& filename);
	~GeneRepository();

	int getSize() const { return this->genes.size(); }
	std::vector<Gene> getGenes() const { return this->genes; }

	void addGene(const Gene& g);
	void updateGene(int index, const Gene& g);

private:
	void loadFromFile();
	void saveToFile();
};

