#ifndef E913_IULIAGROZA_OBSERVER_H
#define E913_IULIAGROZA_OBSERVER_H
#include <vector>
#include <algorithm>

class Observer
{
public:
    virtual void update() = 0;
    virtual ~Observer() {}
};

class Subject
{
private:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* o);
    void removeObserver(Observer* o);
    void notify();
};


#endif
