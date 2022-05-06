#ifndef T2_IULIAGROZA_A_H
#define T2_IULIAGROZA_A_H


#include "Client.h"

class Person : public Client {
public:
    Person();
    Person(std::string &name, const double &income);
    ~Person();

    bool isInterested(Dwelling d) override;
    double totalIncome() override;
    std::string to_string() override;
};


#endif
