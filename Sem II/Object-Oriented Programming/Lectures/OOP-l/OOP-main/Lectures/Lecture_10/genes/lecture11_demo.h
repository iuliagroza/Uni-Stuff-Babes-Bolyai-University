#ifndef LECTURE11_DEMO_H
#define LECTURE11_DEMO_H

#include <QtWidgets/QMainWindow>
#include "ui_lecture11_demo.h"
#include "GeneRepository.h"

using namespace genes;

class Lecture11_demo : public QMainWindow
{
	Q_OBJECT

public:
	Lecture11_demo(GeneRepository& r, QWidget *parent = 0);
	~Lecture11_demo();

private:
	Ui::Lecture11_demoClass ui;
	GeneRepository& repo;

public:
	void genesWidget();
	void genesView();
};

#endif // LECTURE11_DEMO_H
