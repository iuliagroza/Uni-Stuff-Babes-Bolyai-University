#include "GUI.h"

GUI::GUI(Service& service, QWidget* parent) : srv{ service }
{
	ui.setupUi(this);
	this->populate();
}

GUI::~GUI()
{
}

void GUI::populate()
{
	this->ui.tasksListWidget->clear();

	for (auto& t: this->srv.getTasks())
	{
		QString newItem = QString::fromStdString(t.toString());
		QListWidgetItem* item = new QListWidgetItem{ newItem };
		this->ui.tasksListWidget->addItem(item);
	}
}
