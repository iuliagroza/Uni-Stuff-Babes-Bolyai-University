#pragma once
#include <string>
#include <vector>

class Gene
{
private:
	std::string name;
	std::string organismName;
	std::string geneFunction;

public:
	Gene() : name{ "" }, organismName{ "" }, geneFunction{""} {}
	Gene(std::string n, std::string o, std::string f) : name{ n }, organismName{ o }, geneFunction{ f } {}
	std::string getName() const { return this->name; }
	std::string getOrganismName() const { return this->organismName; }
	std::string getGeneFunction() const { return this->geneFunction; }

	void setName(const std::string& val) { this->name = val; }
	void setOrganismName(const std::string& val) { this->organismName = val; }
	void setFunction(const std::string& val) { this->geneFunction = val; }

	std::string toString();

private:
	/*
		Tokenizes a string.
		Input:	str - the string to be tokenized.
		delimiter - char - the delimiter used for tokenization
		Output: a vector of strings, containing the tokens
	*/
	std::vector<std::string> tokenize(std::string str, char delimiter);

	friend std::istream & operator>>(std::istream& is, Gene& g);
};

