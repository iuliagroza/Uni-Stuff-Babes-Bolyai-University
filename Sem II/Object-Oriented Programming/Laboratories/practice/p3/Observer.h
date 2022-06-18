#ifndef P3_OBSERVER_H
#define P3_OBSERVER_H


class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() {};
};


#endif
