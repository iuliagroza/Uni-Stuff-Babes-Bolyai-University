#include "UsersGUI.h"

UsersGUI::UsersGUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// add some elements
	this->users.push_back("Emil | emil@gmail.com");
	this->users.push_back("Adina | adina@gmail.com");

	this->populateList();

	QObject::connect(ui.addButton, &QPushButton::clicked, this, &UsersGUI::addHandler);
}

UsersGUI::~UsersGUI()
{
}

void UsersGUI::populateList()
{
	ui.usersList->clear();

	for (auto elem : this->users)
		ui.usersList->addItem(QString::fromStdString(elem));
}

void UsersGUI::addHandler()
{
	QString name = ui.nameEdit->text();
	QString email = ui.emailEdit->text();

	this->users.push_back(name.toStdString() + " | " + email.toStdString());

	this->populateList();
}
