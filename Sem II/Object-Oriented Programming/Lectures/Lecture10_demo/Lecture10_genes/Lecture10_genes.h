#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lecture10_genes.h"

class Lecture10_genes : public QMainWindow
{
    Q_OBJECT

public:
    Lecture10_genes(QWidget *parent = Q_NULLPTR);

private:
    Ui::Lecture10_genesClass ui;
};
