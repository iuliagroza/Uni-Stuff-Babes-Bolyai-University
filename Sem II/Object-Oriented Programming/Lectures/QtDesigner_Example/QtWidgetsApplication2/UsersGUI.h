#pragma once

#include <QWidget>
#include "ui_UsersGUI.h"
#include <vector>
#include <string>

class UsersGUI : public QWidget
{
	Q_OBJECT

public:
	UsersGUI(QWidget *parent = Q_NULLPTR);
	~UsersGUI();

private:
	Ui::UsersGUI ui;
	std::vector<std::string> users;

public:
	void populateList();
	void addHandler();
};
