#include "Person.h"
#include <fstream>

Person::Person(std::string name): name { name }{}

void Person::addAllAnalyses(const std::string& BMIFilename, const std::string& BPFilename)
{
    /*MedicalAnalysis* bmi = new BMI{ "2022.03.28", 20 };
    MedicalAnalysis* bp = new BP{ "2022.04.14", 100, 80 };
    this->v.push_back(bmi);
    this->v.push_back(bp);*/

    // read from the BMI file
    std::ifstream f{BMIFilename};
    BMI bmi{};
    while (f >> bmi)
    {
        MedicalAnalysis* a = new BMI{ bmi };
        this->v.push_back(a);
    }

    // read from the BP file
    // TO DO
}

std::vector<MedicalAnalysis*> Person::getAllAnalyses()
{
    return this->v;
}

Person::~Person()
{
    for (auto e : this->v)
    {
        delete e;
    }
}
