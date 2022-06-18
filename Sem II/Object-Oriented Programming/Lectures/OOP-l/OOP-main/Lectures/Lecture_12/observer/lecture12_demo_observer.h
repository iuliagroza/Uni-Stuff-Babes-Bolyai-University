#ifndef LECTURE12_DEMO_OBSERVER_H
#define LECTURE12_DEMO_OBSERVER_H

#include <QtWidgets/QMainWindow>
#include "ui_lecture12_demo_observer.h"

class Lecture12_demo_Observer : public QMainWindow
{
	Q_OBJECT

public:
	Lecture12_demo_Observer(QWidget *parent = 0);
	~Lecture12_demo_Observer();

private:
	Ui::Lecture12_demo_ObserverClass ui;
};

#endif // LECTURE12_DEMO_OBSERVER_H
