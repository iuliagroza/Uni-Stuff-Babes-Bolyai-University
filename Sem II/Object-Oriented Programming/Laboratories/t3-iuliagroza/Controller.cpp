#include "Controller.h"
#include <fstream>
#include <algorithm>

void Controller::read_from_file() {
    std::ifstream fin("../input.txt");
    Interval i;

    if(!fin.is_open())
        throw std::exception();
    while(fin >> i) {
        this->intervals.push_back(i);
    }
    fin.close();
}

std::vector<Interval> &Controller::get_intervals() {
    return this->intervals;
}

bool cmp(Interval i1, Interval i2) {
    return i1.get_start_time() < i2.get_start_time() || (i1.get_start_time() == i2.get_start_time() && i1.get_end_time() < i2.get_end_time());
}

void Controller::sort_intervals() {
    std::sort(this->intervals.begin(), this->intervals.end(), cmp);
}
