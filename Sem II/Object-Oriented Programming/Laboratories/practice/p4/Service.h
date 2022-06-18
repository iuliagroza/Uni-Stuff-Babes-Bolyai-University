#ifndef UNTITLED1_SERVICE_H
#define UNTITLED1_SERVICE_H

#include "User.h"
#include "Issue.h"
#include <vector>
#include <fstream>
#include "Observer.h"
#include <algorithm>

class Service : public Subject
{
private:
    std::vector<User> users;
    std::vector<Issue> issues;

public:
    Service() { this->readFromFile(); };

    std::vector<User>& getUsers() { return this->users; }
    std::vector<Issue>& getIssues() { return this->issues; }

    void readFromFile();
    void writeIssuesToFile();

    Issue& operator[](int pos) { return this->issues[pos]; }

    static bool compare(Issue& i1, Issue& e2);
    void sortIssues();

    // Method that adds a new issue by calling predefined function
    // on vector from stl and notifying all users
    void addIssue(Issue& i);

    void removeIssue(Issue& i);

    void updateIssue(std::string desc, std::string status, std::string rep, std::string sol);
};


#endif
