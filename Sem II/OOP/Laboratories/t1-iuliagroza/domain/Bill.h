#ifndef T1_IULIAGROZA_BILL_H
#define T1_IULIAGROZA_BILL_H

#include <string>
using namespace std;

class Bill {
public:
    Bill(string serial_number, string company, string due_date, double sum, bool is_paid);

    Bill();

private:
    string serial_number;
    string company;
    string due_date;
    double sum;
    bool is_paid;

public:
    string get_serial_number() const;
    string get_company() const;
    string get_due_date() const;
    double get_sum() const;
    bool get_is_paid() const;

    string to_str();
};

inline bool operator==(const Bill &a, const Bill &b) {
    return a.get_serial_number() == b.get_serial_number();
}

#endif
