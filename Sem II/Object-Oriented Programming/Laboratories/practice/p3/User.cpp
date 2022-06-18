#include "User.h"

User::User(const std::string &name, const std::string &type) {
    this->name = name;
    this->type = type;
}

std::string User::get_name() {
    return this->name;
}

std::string User::get_type() {
    return this->type;
}

std::vector<std::string> User::tokenize(const std::string& str, char separator)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, separator))
        result.push_back(token);
    return result;
}

std::istream& operator>>(std::istream& is, User& u)
{
    if (is.eof())
        is.setstate(std::ios_base::failbit);
    else
    {
        std::string line;
        getline(is, line);
        std::vector<std::string> tokens = u.tokenize(line, ',');
        if (tokens.size() != 5)
            return is;
        u.name = tokens.at(0);
        u.type = tokens.at(1);
    }
    return is;
}
