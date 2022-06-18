#ifndef P3_SERVICE_H
#define P3_SERVICE_H
#include "Repository.h"
#include "Subject.h"


class Service: public Subject {
private:
    Repository &repository;
public:
    explicit Service(Repository &repository) : repository{repository} {}

    std::vector<Issue> get_issues();
    std::vector<User> get_users();
};

#endif
