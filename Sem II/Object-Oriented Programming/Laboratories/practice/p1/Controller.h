#ifndef P1_CONTROLLER_H
#define P1_CONTROLLER_H
#include <vector>
#include "Task.h"

class Controller {
private:
    std::vector<Task> tasks;

public:
    Controller() {
        this->read_from_file();
        this->sort_tasks();
    }

    void read_from_file();

    std::vector<Task> &get_tasks();

    void sort_tasks();
};


#endif
