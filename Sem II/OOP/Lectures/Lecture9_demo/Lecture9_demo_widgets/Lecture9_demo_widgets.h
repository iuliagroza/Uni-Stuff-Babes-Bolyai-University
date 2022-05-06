#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lecture9_demo_widgets.h"

class Lecture9_demo_widgets : public QMainWindow
{
    Q_OBJECT

public:
    Lecture9_demo_widgets(QWidget *parent = Q_NULLPTR);

private:
    Ui::Lecture9_demo_widgetsClass ui;
};
