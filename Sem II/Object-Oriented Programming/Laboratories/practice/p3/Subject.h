#ifndef P3_SUBJECT_H
#define P3_SUBJECT_H
#include "Observer.h"
#include <vector>
#include <algorithm>


class Subject {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* o);
    void removeObserver(Observer* o);
    void notify();
};


#endif
