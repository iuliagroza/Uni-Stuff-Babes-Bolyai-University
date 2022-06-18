#pragma once
#include "Student.h"
#include <vector>

class Repository
{
private:
	std::vector<Student> students;
	std::string filename;

public:
	Repository(const std::string& filename);

	void addStudent(const Student& s);
	int getSize() const { return this->students.size(); }
	std::vector<Student>& getStudents() { return this->students; }
	Student& operator[](int index) { return students[index]; }

private:
	void readFromFile();
	void writeToFile();
};