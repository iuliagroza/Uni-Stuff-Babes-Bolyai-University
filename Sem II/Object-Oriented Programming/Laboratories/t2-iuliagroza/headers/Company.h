#ifndef T2_IULIAGROZA_B_H
#define T2_IULIAGROZA_B_H


#include "Client.h"

class Company : public Client {
private:
    double moneyFromInvestments;
public:
    Company();
    Company(std::string &name, const double &income, const double &moneyFromInvestments);
    ~Company();

    double totalIncome() override;
    std::string to_string() override;
    bool isInterested(Dwelling d) override;
};


#endif
