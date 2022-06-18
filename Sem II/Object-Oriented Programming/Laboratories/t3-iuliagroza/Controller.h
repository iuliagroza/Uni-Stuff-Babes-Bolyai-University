#ifndef T3_IULIAGROZA_CONTROLLER_H
#define T3_IULIAGROZA_CONTROLLER_H
#include "Interval.h"

class Controller {
private:
    std::vector<Interval> intervals;

public:
    Controller() {
        this->read_from_file();
        this->sort_intervals();
    }

    void read_from_file();

    std::vector<Interval> &get_intervals();

    void sort_intervals();
};


#endif
