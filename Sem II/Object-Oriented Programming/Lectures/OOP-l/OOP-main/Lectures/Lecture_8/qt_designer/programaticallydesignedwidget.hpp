#pragma once
#include <QWidget>

class ProgramaticallyDesignedWidget : public QWidget 
{
public:
	ProgramaticallyDesignedWidget(QWidget * parent = Q_NULLPTR);
	~ProgramaticallyDesignedWidget();

private:
	void initGUI();
};
