#pragma once
#include <string>

class Student
{
private:
	std::string name;
	std::string group;
	double labGrade;
	double seminarGrade;

public:
	Student() { }
	Student(const std::string& n, const std::string& g, double lg, double sg) : name{ n }, group{ g }, labGrade{ lg }, seminarGrade{ sg } {}

	std::string getName() const { return this->name; }
	std::string getGroup() const { return this->group; }
	double getLabGrade() const { return this->labGrade; }
	double getSeminarGrade() const { return this->seminarGrade; }

	void setName(std::string val) { this->name = val; }
	void setLabGrade(double val) { this->labGrade = val; }
	void setSeminarGrade(double val) { this->seminarGrade = val; }

	friend std::istream& operator>>(std::istream& is, Student& s);
	friend std::ostream& operator<<(std::ostream& os, const Student& s);
};

