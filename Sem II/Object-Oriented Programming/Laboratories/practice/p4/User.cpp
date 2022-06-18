#include "User.h"

User::User()
{
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
        if (tokens.size() != 2)
            return is;
        u.name = tokens[0];
        u.type = tokens[1];
    }
    return is;
}
