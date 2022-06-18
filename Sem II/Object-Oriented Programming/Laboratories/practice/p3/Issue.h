#ifndef P3_ISSUE_H
#define P3_ISSUE_H
#include <string>
#include <vector>
#include <sstream>

class Issue {
private:
    std::string description;
    std::string status;
    std::string reporter;
    std::string solver;

public:
    Issue()=default;

    Issue(const std::string& description, const std::string& status, const std::string& reporter, const std::string& solver);

    std::string get_description();

    std::string get_status();

    std::string get_reporter();

    std::string get_solver();

    static std::vector<std::string> tokenize(const std::string& str, char separator);

    friend std::istream &operator>>(std::istream &is, Issue &i);
};


#endif
