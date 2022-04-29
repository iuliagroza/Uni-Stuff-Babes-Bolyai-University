#include "MedicalAnalysis.h"
#include <sstream>
#include <vector>
#include "Utils.h"

MedicalAnalysis::MedicalAnalysis(const std::string& date)
{
	this->date = date;
}

std::string MedicalAnalysis::toString() const
{	
	return date;
}

BMI::BMI(): MedicalAnalysis{""}, value{0}
{
}

BMI::BMI(const std::string& date, double value):MedicalAnalysis{date},value{value}{}

bool BMI::isResultOk() const
{
	if (value > 18.5 && value < 25)
		return true;
	return false;
}

std::string BMI::toString() const
{	
	std::stringstream ss;
	ss << date << ", " << value;
	return ss.str();
}

std::istream& BMI::read(std::istream& is)
{
	std::string line;
	getline(is, line);

	std::vector<std::string> tokens = tokenize(line, ',');
	if (tokens.size() != 2)
		return is;
	this->date = tokens[0];
	this->value = stod(tokens[1]);
	return is;
}

BP::BP(const std::string& date, int sys, int dia):MedicalAnalysis{date},systolic{sys},diastolic{dia}{}

bool BP::isResultOk() const
{	
	if ((systolic >= 90 && systolic <= 119) && (diastolic >= 60 && diastolic <= 79))
		return true;
	return false;
}

std::string BP::toString() const 
{	
	std::stringstream ss;
	ss << date << ", " << systolic << ", " << diastolic;
	return ss.str();
}

std::istream& BP::read(std::istream& is)
{
	// TODO
	return is;
}

std::istream& operator>>(std::istream& is, MedicalAnalysis& a)
{
	return a.read(is);
}

std::ostream& operator<<(std::ostream& os, const MedicalAnalysis& a)
{
	os << a.toString() << std::endl;
	return os;
}
