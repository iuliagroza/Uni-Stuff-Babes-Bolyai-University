#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lecture10_introspection.h"

class Lecture10_introspection : public QMainWindow
{
    Q_OBJECT

public:
    Lecture10_introspection(QWidget *parent = Q_NULLPTR);

private:
    Ui::Lecture10_introspectionClass ui;
};
