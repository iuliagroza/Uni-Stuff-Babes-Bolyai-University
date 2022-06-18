#include "Observer.h"

void Subject::addObserver(Observer* o)
{
    this->observers.push_back(o);
}

void Subject::removeObserver(Observer* o)
{
    auto it = std::find(this->observers.begin(), this->observers.end(), o);

    if (it != this->observers.end())
        this->observers.erase(it);
}

void Subject::notify()
{
    for (auto o : this->observers)
        o->update();
}
