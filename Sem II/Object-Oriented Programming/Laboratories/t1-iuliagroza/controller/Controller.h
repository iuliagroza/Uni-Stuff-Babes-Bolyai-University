#ifndef T1_IULIAGROZA_CONTROLLER_H
#define T1_IULIAGROZA_CONTROLLER_H

#include "../repository/Repository.h"

class Controller {
private:
    Repository repo;

public:
    Repository get_repo();
    bool remove(Bill bill);
    void generate_instances();
    double unpaid_bills();
};


#endif
