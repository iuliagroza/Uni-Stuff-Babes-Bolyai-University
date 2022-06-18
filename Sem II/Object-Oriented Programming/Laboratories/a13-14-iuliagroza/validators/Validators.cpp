#include "Validators.h"

bool Validators::is_number(const std::string &str) {
    for (char const &c: str) {
        if (std::isdigit(c) == 0) {
            return false;
        }
    }
    return true;
}

void Validators::validate_option(std::string login_ipt, std::vector<std::string> options) {
    std::vector<std::string>::iterator it = find(options.begin(), options.end(), login_ipt);
    if (it == options.end()) {
        throw InputError("Invalid input.");
    }
}
