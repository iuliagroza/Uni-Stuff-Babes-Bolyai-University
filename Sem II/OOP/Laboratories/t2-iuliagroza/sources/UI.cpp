#include "../headers/UI.h"

UI::UI(RealEstateAgency service) {
    this->service = service;
}

UI::UI() {

}

UI::~UI() {

}


void menu() {
    std::cout << "Choose a command by typing its corresponding number:\n"
                 "1. Remove a client.\n"
                 "2. Show all clients.\n"
                 "3. Show all dwellings.\n"
                 "4. Display all the movies.\n"
                 "5. Exit\n";
}

bool validate_option(const std::string& login_ipt, std::vector<std::string> options) {
    auto it = find(options.begin(), options.end(), login_ipt);
    if (it == options.end()) {
        return false;
    }
    return true;
}

std::string menu_input(int number_of_commands) {
    std::string ipt;
    std::vector<std::string> options;

    for (int i = 1; i <= number_of_commands; i++) {
        options.push_back(std::to_string(i));
    }

    while (find(options.begin(), options.end(), ipt) == options.end()) {
        std::cout << ">>> ";
        getline(std::cin, ipt);

        if(!validate_option(ipt, options)) {
            std::cout << "Invalid input.\n";
        } else {
            break;
        }
    }

    return ipt;
}

void UI::display_clients() {
    auto a = this->service.get_clients();
    for(auto &i : a){
        std::cout << i->to_string();
    }
}

void UI::display_dwellings() {
    for(auto d : this->service.get_dwellings()) {
        std::cout << "Price: " << std::to_string(d.get_price()) << "; isProfitable: " << std::to_string(d.get_is_profitable()) << "\n";
    }
}

void UI::start() {
    this->service.generate();
    while (true) {
        menu();

        std::string ipt = menu_input(6);

        if (ipt == "1") {
            break;
        } else if (ipt == "2") {
            this->display_clients();
        } else if (ipt == "3") {
            this->display_dwellings();
        } else if (ipt == "4") {
            break;
        } else {
            break;
        }
    }
}
