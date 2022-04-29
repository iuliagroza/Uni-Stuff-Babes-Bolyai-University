#include "Repository.h"

DynamicArray<Bill> Repository::get_bills() {
    return this->bills;
}

void Repository::add_bill(Bill bill) {
    this->bills.add(bill);
}

bool Repository::remove_bill(Bill bill) {
    int position = find_bill(bill);
    if(position == -1) {
        return false;
    }

    this->bills.remove(position);
    return true;
}

int Repository::find_bill(Bill bill) {
    for (int i = 0; i < this->bills.get_size(); i++) {
        if (this->bills.get_element(i) == bill) {
            return i;
        }
    }
    return -1;
}