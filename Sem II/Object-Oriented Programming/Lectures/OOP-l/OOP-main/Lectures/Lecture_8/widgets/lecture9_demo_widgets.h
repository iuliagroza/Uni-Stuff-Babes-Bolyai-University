#ifndef LECTURE9_DEMO_WIDGETS_H
#define LECTURE9_DEMO_WIDGETS_H

#include <QtWidgets/QMainWindow>
#include "ui_lecture9_demo_widgets.h"

class Lecture9_demo_widgets : public QMainWindow
{
	Q_OBJECT

public:
	Lecture9_demo_widgets(QWidget *parent = 0);
	~Lecture9_demo_widgets();

private:
	Ui::Lecture9_demo_widgetsClass ui;
};

#endif // LECTURE9_DEMO_WIDGETS_H
