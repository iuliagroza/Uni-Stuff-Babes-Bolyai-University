#include "Dwelling.h"



class Client{
protected:

    std::string name;
    double income;

public:

    Client(){ this->income = 0; this->name = "";};

    virtual ~Client()= default;

    std::string getName(){return this->name;};

    virtual double totalIncome() = 0;

    virtual bool isInterested(Dwelling* d) = 0;

    virtual std::string to_string() = 0;


};

class Person: public Client{
public:
    Person(){ this->income = 0; this->name = "";};

    Person(double inc, const std::string& nam);

    ~Person() override = default;

    bool isInterested(Dwelling* d) override;

    double totalIncome() override {
        return this->income;
    }

    std::string to_string() override;
};

class Company: public Client{
private:
    double moneyFromInvestments;

public:

    Company(){ this->income = 0; this->name="";  this->moneyFromInvestments = 0;};

    Company(double inc, std::string nam, double money);

    ~Company() override = default;

    bool isInterested(Dwelling* d) override;

    double totalIncome() override {
        return this->income + this->moneyFromInvestments;
    }

    std::string to_string() override;
};