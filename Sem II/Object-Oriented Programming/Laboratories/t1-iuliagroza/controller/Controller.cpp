#include "Controller.h"
#include <iostream>

Repository Controller::get_repo() {
    return this->repo;
}

/*
 * Calculates total sum of unpaid bills.
 * :return: double
 * */
double Controller::unpaid_bills() {
    double sum = 0;
    for(int i=0; i<this->repo.get_bills().get_size(); i++) {
        if(this->repo.get_bills().get_element(i).get_is_paid() == false) {
            sum += this->repo.get_bills().get_element(i).get_sum();
        }
    }

    return sum;
}

/*
 * Removes a bill from the controller.
 * :return: bool
 * */
bool Controller::remove(Bill bill) {
    return this->repo.remove_bill(bill);
}

void Controller::generate_instances() {
    this->repo.add_bill(Bill("SD2W32F3", "Digi Sport", "15.04.2016", 75.00, false));
    this->repo.add_bill(Bill("ASDS4TEW", "E-On", "16.03.2016", 122.00, true));
    this->repo.add_bill(Bill("G342ED3F", "Orange", "18.04.2016", 46.00, false));
    this->repo.add_bill(Bill("ADF64W5G", "Vodafone", "20.04.2016", 23.00, false));
    this->repo.add_bill(Bill("SADS344R", "Tcomm", "21.04.2016", 10.00, true));
}
