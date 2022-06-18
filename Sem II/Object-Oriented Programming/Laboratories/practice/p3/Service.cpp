#include "Service.h"
#include <algorithm>

std::vector<User> Service::get_users() {
    return this->repository.get_users();
}

std::vector<Issue> Service::get_issues() {
    return this->repository.get_issues();
}