#include "Service.h"

void Service::readFromFile()
{
    std::ifstream file{ "../inputUsers.txt" };
    if (!file.is_open())
        throw std::exception();
    User t;
    while (file >> t)
    {
        this->users.push_back(t);
    }

    file.close();

    std::ifstream file1{ "../inputIssues.txt" };
    if (!file1.is_open())
        throw std::exception();
    Issue i;
    while (file1 >> i)
    {
        this->issues.push_back(i);
    }

    file1.close();
}

void Service::writeIssuesToFile()
{
    std::ofstream file{ "inputIssues.txt" };

    if (!file.is_open())
        throw std::exception();

    for (auto& i : this->issues)
    {
        file << i.getDescription() + ',' + i.getStatus() + ',' + i.getReporter() + ',' + i.getSolver() + '\n';
    }
    file.close();
}

bool Service::compare(Issue& i1, Issue& e2)
{
    return (i1.getStatus()  < e2.getStatus()) || ((i1.getStatus() == e2.getStatus()) && (i1.getDescription() < e2.getDescription()));
}

void Service::sortIssues()
{
    std::sort(this->issues.begin(), this->issues.end(), compare);
}

void Service::addIssue(Issue& i)
{
    this->issues.push_back(i);
    this->notify();
}

void Service::removeIssue(Issue& i)
{
    auto it = this->issues.begin();

    for (auto& x : this->issues)
    {
        if (i.getDescription() == x.getDescription())
        {
            this->issues.erase(it);
            this->notify();
            return;
        }
        it++;
    }
}

void Service::updateIssue(std::string desc, std::string status, std::string rep, std::string sol)
{
    auto it = this->issues.begin();

    for (auto& x : this->issues)
    {
        if (desc == x.getDescription())
        {
            x.setSolver(sol);
            x.setStatus(status);
            this->notify();
            return;
        }
        it++;
    }
}
