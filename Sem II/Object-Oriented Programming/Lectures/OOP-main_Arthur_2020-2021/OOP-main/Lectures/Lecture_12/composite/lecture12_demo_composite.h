#ifndef LECTURE12_DEMO_COMPOSITE_H
#define LECTURE12_DEMO_COMPOSITE_H

#include <QtWidgets/QMainWindow>
#include "ui_lecture12_demo_composite.h"
#include <QPainter>
#include <memory>
#include <vector>

class Lecture12_demo_Composite : public QMainWindow
{
	Q_OBJECT

public:
	Lecture12_demo_Composite(QWidget *parent = 0);
	~Lecture12_demo_Composite();

private:
	Ui::Lecture12_demo_CompositeClass ui;

	std::vector<Graphic*> graphics;

	void initializeGraphics();
	void populateList();
};

#endif // LECTURE12_DEMO_COMPOSITE_H
