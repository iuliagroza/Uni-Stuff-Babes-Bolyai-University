#ifndef P3_USER_H
#define P3_USER_H
#include <string>
#include <vector>
#include <sstream>

class User {
private:
    std::string name, type;
public:
    User()=default;
    User(const std::string &name, const std::string &type);

    std::string get_name();
    std::string get_type();

    static std::vector<std::string> tokenize(const std::string& str, char separator);

    friend std::istream &operator>>(std::istream &is, User &u);
};


#endif
