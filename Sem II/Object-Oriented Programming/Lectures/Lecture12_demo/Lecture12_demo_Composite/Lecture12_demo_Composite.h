#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lecture12_demo_Composite.h"
#include <QPainter>
#include <memory>
#include <vector>

class Lecture12_demo_Composite : public QMainWindow
{
	Q_OBJECT

public:
	Lecture12_demo_Composite(QWidget* parent = 0);
	~Lecture12_demo_Composite();

private:
	Ui::Lecture12_demo_CompositeClass ui;

	std::vector<Graphic*> graphics;

	void initializeGraphics();
	void populateList();
};
