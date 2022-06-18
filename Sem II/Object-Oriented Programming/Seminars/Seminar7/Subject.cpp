#include <algorithm>
#include "Subject.h"

void Subject::registerObserver(Observer *obs) {
    this->observers.push_back(obs);
}

void Subject::unregisterObserver(Observer *obs) {
    auto it = std::find(this->observers.begin(), this->observers.end(), obs);
    if(it != this->observers.end()) {
        this->observers.erase(it);
    }
}

void Subject::notify() {
    for(auto &observer : this->observers) {
        observer->update();
    }
}
