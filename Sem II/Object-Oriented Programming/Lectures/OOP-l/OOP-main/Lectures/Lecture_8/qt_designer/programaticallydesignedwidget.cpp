#include "programaticallydesignedwidget.hpp"
#include <QVBoxLayout>
#include <vector>
#include <numeric>
#include <algorithm>
#include <QLabel>
#include <time.h>
#include <QPushButton>
#include <QApplication>

ProgramaticallyDesignedWidget::ProgramaticallyDesignedWidget(QWidget* parent) : QWidget{parent}
{	
	this->initGUI();
}

ProgramaticallyDesignedWidget::~ProgramaticallyDesignedWidget() 
{
}

void ProgramaticallyDesignedWidget::initGUI()
{
	srand(time(NULL)); // set a seed for the rand() function

	QVBoxLayout* vLayout = new QVBoxLayout{ this };

	// randomly choose 6 numbers, from 1 to 49 and show them
	std::vector<int> v(6);
	std::iota(v.begin(), v.end(), 0); // fill the vector with sequentially incresing values

	std::vector<int> alreadyGenerated;

	// generate numbers one by one
	for (auto i : v)
	{
		int randNum = rand() % 49 + 1;
		while (std::find(alreadyGenerated.begin(), alreadyGenerated.end(), randNum) != alreadyGenerated.end())
			randNum = rand() % 49 + 1;

		// create uneditable edit boxes with the generated numbers
		QLabel* no = new QLabel{ QString::number(randNum) };
		QFont font("Courier", 40, 10, true);
		no->setFont(font);

		alreadyGenerated.push_back(randNum);

		vLayout->addWidget(no);
	}

	// add a close button, with a slot
	QPushButton *closeButton = new QPushButton("&Close");
	QObject::connect(closeButton, &QPushButton::clicked, QApplication::instance(), &QApplication::quit);
	
	vLayout->addWidget(closeButton);
}
