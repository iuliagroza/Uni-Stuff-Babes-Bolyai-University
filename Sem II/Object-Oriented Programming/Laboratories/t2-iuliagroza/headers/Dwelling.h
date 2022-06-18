#pragma once

#include <iostream>

class Dwelling {
private:

    double price;
    bool isProfitable;

public:

    bool getProfitable() const { return this->isProfitable; };

    double getPrice() const { return this->price; };

    Dwelling() {
        this->price = 0;
        this->isProfitable = false;
    };

    Dwelling(double pri, bool is) {
        this->price = pri;
        this->isProfitable = is;
    }

    virtual ~Dwelling() = default;

    std::string to_string() const {
        std::string f;
        f += "price: " + std::to_string(this->price) + "  is profitable: " + std::to_string(this->isProfitable);
        return f;
    }
};

