#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lecture9_demo.h"

class Lecture9_demo : public QMainWindow
{
    Q_OBJECT

public:
    Lecture9_demo(QWidget *parent = Q_NULLPTR);

private:
    Ui::Lecture9_demoClass ui;
};
