#include "TeachersWindow.h"

TeachersWindow::TeachersWindow(QAbstractItemModel* model, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.studentsTableView->setModel(model);
}

TeachersWindow::~TeachersWindow()
{
}
