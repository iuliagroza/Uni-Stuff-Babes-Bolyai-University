#include "lecture11_demo.h"
#include "DialogGenesListWidget.h"
#include "DialogGenesView.h"
#include <ctime>
#include <QMessageBox>

Lecture11_demo::Lecture11_demo(GeneRepository& r, QWidget *parent) : QMainWindow(parent), repo{ r }
{
	ui.setupUi(this);

	QObject::connect(ui.GenesWidgetButton, &QPushButton::clicked, this, &Lecture11_demo::genesWidget);
	QObject::connect(ui.GenesViewButton, &QPushButton::clicked, this, &Lecture11_demo::genesView);
}

Lecture11_demo::~Lecture11_demo()
{
}

void Lecture11_demo::genesWidget()
{
	this->setCursor(Qt::WaitCursor);

	// get the time needed for populating and displaying the list widget
	clock_t beginTime = clock();

	DialogGenesListWidget* dlg = new DialogGenesListWidget{repo};
	dlg->show();

	clock_t endTime = clock();

	this->setCursor(Qt::ArrowCursor);
	QMessageBox::information(dlg, "Time", "<font size = 20 > " + QString::number((double)(endTime - beginTime) / CLOCKS_PER_SEC) + " seconds to load and display the list." + "</font>");
}

void Lecture11_demo::genesView()
{
	this->setCursor(Qt::WaitCursor);

	// get the time needed for populating and displaying the list view
	clock_t beginTime = clock();

	DialogGenesView* dlg = new DialogGenesView{repo};
	dlg->show();

	clock_t endTime = clock();

	this->setCursor(Qt::ArrowCursor);
	QMessageBox::information(dlg, "Time", "<font size = 20 > " + QString::number((double)(endTime - beginTime) / CLOCKS_PER_SEC) + " seconds to load and display the list." + "</font>");
}
