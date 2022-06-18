#include "Repository.h"
#include <fstream>
#include <sstream>
#include <algorithm>

Repository::Repository() {
    this->readFromFile();
}

void Repository::readFromFile() {
    std::ifstream fin_u("../users.txt");
    User u;

    if(!fin_u.is_open())
        throw std::exception();
    while(fin_u >> u) {
        this->users.push_back(u);
    }
    fin_u.close();

    std::ifstream fin_i("../issues.txt");
    Issue i;

    if(!fin_i.is_open())
        throw std::exception();
    while(fin_i >> u) {
        this->issues.push_back(i);
    }
    fin_i.close();
}