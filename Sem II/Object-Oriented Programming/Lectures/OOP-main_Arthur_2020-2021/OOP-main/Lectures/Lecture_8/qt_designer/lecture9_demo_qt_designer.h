#ifndef LECTURE9_DEMO_QT_DESIGNER_H
#define LECTURE9_DEMO_QT_DESIGNER_H

#include <QtWidgets/QMainWindow>
#include "ui_lecture9_demo_qt_designer.h"

class Lecture9_demo_Qt_designer : public QMainWindow
{
	Q_OBJECT

public:
	Lecture9_demo_Qt_designer(QWidget *parent = 0);
	~Lecture9_demo_Qt_designer();

	void populateList();

private:
	Ui::Lecture9_demo_Qt_designerClass ui;
};

#endif // LECTURE9_DEMO_QT_DESIGNER_H
