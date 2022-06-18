#ifndef UNTITLED1_USER_H
#define UNTITLED1_USER_H
#include <string>
#include <sstream>
#include <vector>


class User {
private:
    std::string name;
    std::string type;

public:
    User();
    User(const std::string& name, const std::string& type): name{name}, type{type}{}

    std::string getName() { return this->name; };
    std::string getType() { return this->type; };

    std::vector<std::string> tokenize(const std::string& str, char separator);
    friend std::istream& operator>>(std::istream& is, User& u);
};


#endif
