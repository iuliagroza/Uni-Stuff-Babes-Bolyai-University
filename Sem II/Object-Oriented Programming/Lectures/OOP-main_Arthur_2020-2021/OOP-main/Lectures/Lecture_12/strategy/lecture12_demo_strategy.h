#ifndef LECTURE12_DEMO_STRATEGY_H
#define LECTURE12_DEMO_STRATEGY_H

#include <QtWidgets/QMainWindow>
#include "ui_lecture12_demo_strategy.h"
#include "SaveFileStrategy.h"

class Lecture12_demo_Strategy : public QMainWindow
{
	Q_OBJECT

private:
	std::unique_ptr<SaveFileStrategy> saveFileStrategy;
	std::unique_ptr<CreateStrategy> creatorStrategy;
	std::vector<strategy::Castle> castles;

public:
	Lecture12_demo_Strategy(QWidget *parent = 0);
	~Lecture12_demo_Strategy();

private:
	Ui::Lecture12_demo_StrategyClass ui;
	std::string getFilename(FileType fileType);
	void saveFile(const std::string& filename, FileType fileType);
	void showFileContent(const std::string& filename, FileType fileType);
};

#endif // LECTURE12_DEMO_STRATEGY_H
