#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lecture10_notepad.h"
#include <QtWidgets/qtextedit.h>

class Lecture10_Notepad : public QMainWindow
{
	Q_OBJECT

public:
	Lecture10_Notepad(QWidget* parent = 0);
	~Lecture10_Notepad();

	void buildWindow();

private:
	Ui::Lecture10_notepadClass ui;

	QMenu* fileMenu;
	QAction* openAction;
	QAction* saveAction;
	QAction* exitAction;
	QTextEdit* textEdit;

	std::string filename;

	void connectSignalsAndSlots();

	void open();
	void save();
};

