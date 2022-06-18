#ifndef SEMINAR7_SUBJECT_H
#define SEMINAR7_SUBJECT_H


#include <vector>
#include "Observer.h"

class Subject {
private:
    std::vector<Observer*> observers;
public:
    void registerObserver(Observer *obs);
    void unregisterObserver(Observer *obs);
    void notify();
};


#endif
