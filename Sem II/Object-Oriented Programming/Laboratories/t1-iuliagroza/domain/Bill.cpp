#include "Bill.h"
#include <sstream>

string Bill::get_serial_number() const {
    return this->serial_number;
}

string Bill::get_company() const {
    return this->company;
}

string Bill::get_due_date() const {
    return this->due_date;
}

double Bill::get_sum() const {
    return this->sum;
}

bool Bill::get_is_paid() const {
    return this->is_paid;
}

Bill::Bill(string serial_number, string company, string due_date, double sum, bool is_paid) {
    this->serial_number = serial_number;
    this->company = company;
    this->due_date = due_date;
    this->sum = sum;
    this->is_paid = is_paid;
}

Bill::Bill() {
    this->serial_number = "";
    this->company = "";
    this->due_date = "";
    this->sum = 0;
    this->is_paid = false;
}

/*Bill &Bill::operator=(const Bill &bill) {
    if (this == &bill)
        return *this;

    this->serial_number = bill.serial_number;
    this->company = bill.company;
    this->due_date = bill.due_date;
    this->sum = bill.sum;
    this->is_paid = bill.is_paid;

    return *this;
}*/

string Bill::to_str() {
    ostringstream output;

    output << "Serial Number: " << this->serial_number << "; ";
    output << "Company: " << this->company << "; ";
    output << "Due Date: " << this->due_date << "; ";
    output << "Sum: " << this->sum << "; ";
    if(this->is_paid) {
        output << "Is paid: yes\n";
    } else {
        output << "Is paid: no\n";
    }

    return output.str();
}
