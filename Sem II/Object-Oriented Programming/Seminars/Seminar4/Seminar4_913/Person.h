#pragma once
#include <string>
#include <vector>
#include "MedicalAnalysis.h"

class Person
{
private:
	std::string name;
	std::vector<MedicalAnalysis*> v;

public:
	Person(std::string name);

	void addAllAnalyses(const std::string& BMIFilename, const std::string& BPFilename);
	
	std::vector<MedicalAnalysis*> getAllAnalyses();

	~Person();

};

