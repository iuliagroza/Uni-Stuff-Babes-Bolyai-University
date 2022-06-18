#ifndef P3_REPOSITORY_H
#define P3_REPOSITORY_H
#include "Issue.h"
#include "User.h"
#include <vector>


class Repository {
private:
    std::vector<User> users;
    std::vector<Issue> issues;

public:
    Repository();

    std::vector<User> get_users() {
        return this->users;
    }

    std::vector<Issue> get_issues() {
        return this->issues;
    }

    void readFromFile();
};


#endif
