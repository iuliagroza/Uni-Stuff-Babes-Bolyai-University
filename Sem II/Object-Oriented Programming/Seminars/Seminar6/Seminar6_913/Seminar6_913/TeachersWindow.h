#pragma once

#include <QWidget>
#include "ui_TeachersWindow.h"
#include <QAbstractItemModel>
#include <memory>

class TeachersWindow : public QWidget
{
	Q_OBJECT

public:
	TeachersWindow(QAbstractItemModel* model, QWidget* parent = Q_NULLPTR);
	~TeachersWindow();

private:
	Ui::TeachersWindow ui;
};
