#include "Repository.h"

void Repository::readFromFile()
{
    std::ifstream file{ "../questions.txt" };
    if (!file.is_open())
        throw std::exception();
    Question q;
    while (file >> q)
    {
        this->questions.push_back(q);
    }

    file.close();

    std::ifstream file1{ "../participants.txt" };
    if (!file1.is_open())
        throw std::exception();
    Participant p;
    while (file1 >> p)
    {
        this->participants.push_back(p);
    }

    file1.close();
}

void Repository::addQuestion(Question &q) {
    this->questions.push_back(q);
}
