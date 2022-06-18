#ifndef LECTURE12_DEMO_ADAPTER_H
#define LECTURE12_DEMO_ADAPTER_H

#include <QtWidgets/QMainWindow>
#include "ui_lecture12_demo_adapter.h"
#include "Controller.h"

class Lecture12_demo_Adapter : public QMainWindow
{
	Q_OBJECT

private:
	Controller& ctrl;
public:
	Lecture12_demo_Adapter(Controller& c, QWidget *parent = 0);
	~Lecture12_demo_Adapter();

private:
	Ui::Lecture12_demo_AdapterClass ui;

	void populateList();
	void setCurrentCastle();

	void connectButtons();
};

#endif // LECTURE12_DEMO_ADAPTER_H
