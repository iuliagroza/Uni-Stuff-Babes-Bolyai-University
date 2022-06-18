#include "MedicalAnalysis.h"
#include <iostream>
#include "ui.h"
#include <fstream>

using namespace std;

int main() {
	Person person = Person("test");
	person.addAllAnalyses("BMI.txt", "BP.txt");
	UI ui = UI(person);

	ui.run();

	return 0;
}