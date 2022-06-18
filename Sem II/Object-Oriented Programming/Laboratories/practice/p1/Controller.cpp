#include "Controller.h"
#include <fstream>
#include <iostream>
#include <algorithm>

void Controller::read_from_file() {
    std::ifstream fin("../input.txt");
    Task t;

    if(!fin.is_open())
        throw std::exception();
    while(fin >> t) {
        this->tasks.push_back(t);
    }
    fin.close();
}

std::vector<Task> &Controller::get_tasks() {
    return this->tasks;
}

bool cmp(Task t1, Task t2) {
    return t1.get_priority() < t2.get_priority() || (t1.get_priority() == t2.get_priority() && t1.get_duration() < t2.get_duration());
}

void Controller::sort_tasks() {
    std::sort(this->tasks.begin(), this->tasks.end(), cmp);
}