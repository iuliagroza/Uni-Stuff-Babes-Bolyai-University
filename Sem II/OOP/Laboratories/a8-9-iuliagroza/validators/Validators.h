#ifndef A8_9_IULIAGROZA_VALIDATORS_H
#define A8_9_IULIAGROZA_VALIDATORS_H

#include "Exceptions.h"
#include <vector>
#include <algorithm>
#include <string>

class Validators {
public:
    bool is_number(const std::string &str);

    void validate_option(std::string login_ipt, std::vector<std::string> options);
};


#endif
