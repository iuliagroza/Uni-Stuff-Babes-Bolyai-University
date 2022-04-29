#include "UI.h"
#include <iostream>

using namespace std;

void UI::start_menu() {
    cout << "Welcome to your Bill Management App! Choose a command by typing its corresponding number:\n"
            "1. Remove a bill.\n"
            "2. Display all the bills.\n"
            "3. Display and sort all the unpaid bill by their due_date.\n"
            "4. Display the total sum of unpaid bills.\n"
            "5. Exit\n";
}

string UI::input() {
    string ipt;

    while (ipt != "1" && ipt != "2" && ipt != "3" && ipt != "4" && ipt != "5") {
        cout << ">>> ";
        getline(cin, ipt);

        if (ipt != "1" && ipt != "2" && ipt != "3" && ipt != "4" && ipt != "5") {
            cout << "Invalid input.\n";
        }
    }

    return ipt;
}

void UI::remove_UI() {
    string serial_number;
    cout << "Please type the serial number of the bill: ";
    getline(cin, serial_number);
    bool result = this->ctrl.remove(Bill(serial_number, "a", "b", 0, true));
    if(result) {
        cout << "Bill removed successfully.\n";
    } else {
        cout << "This bill does not exist in the database.\n";
    }
}

void UI::display_sum_unpaid() {
    cout << this->ctrl.unpaid_bills() << '\n';
}

void UI::display_sort() {
    for(int i=0; i<this->ctrl.get_repo().get_bills().get_size()-1; i++) {
        for(int j=i+1; j<this->ctrl.get_repo().get_bills().get_size(); j++) {
            if(this->ctrl.get_repo().get_bills().get_element(i).get_sum() < this->ctrl.get_repo().get_bills().get_element(j).get_sum()) {
                
            }
        }
    }
}

void UI::display_bills() {
    for(int i=0; i<this->ctrl.get_repo().get_bills().get_size(); i++) {
        cout << i+1 << ". " << this->ctrl.get_repo().get_bills().get_element(i).to_str();
    }
}

void UI::start() {
    this->ctrl.generate_instances();
    while (true) {
        start_menu();
        string ipt = input();

        if (ipt == "1") {
            remove_UI();
        } else if (ipt == "2") {
            display_bills();
        } else if (ipt == "3") {
            break;
        } else if (ipt == "4") {
            display_sum_unpaid();
        } else {
            break;
        }
    }
}