#pragma once
#include <string>
#include <iostream>

class MedicalAnalysis
{
protected:
	std::string date;
public:
	MedicalAnalysis(const std::string& date);

	virtual bool isResultOk() const = 0;
	virtual std::string toString() const;

	virtual ~MedicalAnalysis() {}
	virtual std::istream& read(std::istream& is) = 0;

	friend std::istream& operator>>(std::istream& is, MedicalAnalysis& a);
	friend std::ostream& operator<<(std::ostream& os, const MedicalAnalysis& a);
};

class BMI : public MedicalAnalysis
{
private:
	double value;
public:
	BMI();
	BMI(const std::string& date, double value);

	bool isResultOk() const override;
	std::string toString() const override;

	std::istream& read(std::istream& is) override;
};

class BP : public MedicalAnalysis
{
private:
	int systolic;
	int diastolic;
public:

	BP(const std::string& date, int sys, int dia);

	bool isResultOk() const override;
	std::string toString() const override;

	std::istream& read(std::istream& is) override;
};
