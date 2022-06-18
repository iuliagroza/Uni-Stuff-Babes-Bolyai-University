#include "Service.h"

void Service::readFromFile()
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

bool Service::cmp(Question &q1, Question &q2) {
    return (q1.getId() < q2.getId());
}

void Service::sort()
{
    std::sort(this->questions.begin(), this->questions.end(), cmp);
}

void Service::addQuestion(Question &q) {
    this->questions.push_back(q);
    this->notify();
}

void Service::writeToFile()
{
    std::ofstream file1{ "../questions.txt" };

    if (!file1.is_open())
        throw std::exception();

    for (auto& i : this->questions)
    {
        file1 << std::to_string(i.getId()) + ',' + i.getText() + ',' + i.getAnswer() + ',' + std::to_string(i.getScore()) + '\n';
    }
    file1.close();

    std::ofstream file2{ "../participants.txt" };

    if (!file2.is_open())
        throw std::exception();

    for (auto& i : this->participants)
    {
        file2 << i.getName() + ',' + std::to_string(i.getScore()) + '\n';
    }
    file2.close();
}