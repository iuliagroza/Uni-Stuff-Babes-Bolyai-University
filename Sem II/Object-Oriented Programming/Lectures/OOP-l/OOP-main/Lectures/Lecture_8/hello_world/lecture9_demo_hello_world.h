#ifndef LECTURE9_DEMO_HELLO_WORLD_H
#define LECTURE9_DEMO_HELLO_WORLD_H

#include <QtWidgets/QMainWindow>
#include "ui_lecture9_demo_hello_world.h"

class Lecture9_demo_Hello_world : public QMainWindow
{
	Q_OBJECT

public:
	Lecture9_demo_Hello_world(QWidget *parent = 0);
	~Lecture9_demo_Hello_world();

private:
	Ui::Lecture9_demo_Hello_worldClass ui;
};

#endif // LECTURE9_DEMO_HELLO_WORLD_H
