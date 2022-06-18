#ifndef UNTITLED1_ISSUE_H
#define UNTITLED1_ISSUE_H
#include <string>
#include <sstream>
#include <vector>


class Issue {
private:
    std::string description;
    std::string status;
    std::string reporter;
    std::string solver;

public:
    Issue();
    Issue(const std::string& desc, const std::string& status, const std::string& rep, const std::string& solv): description{desc}, status{status}, reporter{rep}, solver{solv}{}

    std::string getDescription() { return this->description; }
    std::string getStatus() { return this->status; }
    std::string getReporter() { return this->reporter; }
    std::string getSolver() { return this->solver; }

    void setStatus(const std::string& s) { this->status = s; }
    void setReporter(const std::string& s) { this->reporter = s; }
    void setSolver(const std::string& s) { this->solver = s; }

    std::vector<std::string> tokenize(const std::string& str, char separator);
    friend std::istream& operator>>(std::istream& is, Issue& i);
};


#endif
