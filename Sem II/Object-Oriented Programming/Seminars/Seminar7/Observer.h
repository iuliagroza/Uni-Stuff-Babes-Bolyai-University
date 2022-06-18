#ifndef SEMINAR7_OBSERVER_H
#define SEMINAR7_OBSERVER_H


class Observer {
public:
    virtual void update()=0;
    virtual ~Observer();
};


#endif
