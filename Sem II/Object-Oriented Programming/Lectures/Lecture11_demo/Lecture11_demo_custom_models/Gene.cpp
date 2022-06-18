#include "Gene.h"
#include <sstream>

std::string Gene::toString()
{
	std::stringstream s;
	s << this->organismName << "|" << this->name << "|" << this->geneFunction<<std::endl;
	return std::string(s.str());
}

std::vector<std::string> Gene::tokenize(std::string str, char delimiter)
{
	std::vector <std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

std::istream& operator>>(std::istream& is, Gene& g)
{
	std::string line;
	getline(is, line);

	std::vector<std::string> tokens = g.tokenize(line, '|');
	if (tokens.size() != 3) // make sure all the gene data was valid
		return is;
	g.organismName = tokens[0];
	g.name = tokens[1];
	g.geneFunction = tokens[2];

	return is;
}
