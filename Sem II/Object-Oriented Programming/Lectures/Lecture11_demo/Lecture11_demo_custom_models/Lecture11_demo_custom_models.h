#ifndef LECTURE11_DEMO_CUSTOM_MODELS_H
#define LECTURE11_DEMO_CUSTOM_MODELS_H

#include <QtWidgets/QMainWindow>
#include "ui_lecture11_demo_custom_models.h"
#include "GeneRepository.h"
#include "GenesTableModel.h"

class Lecture11_demo_custom_models : public QMainWindow
{
	Q_OBJECT

private:
	GeneRepository& repo;
	GenesTableModel* tableModel;
	Ui::Lecture11_demo_custom_modelsClass ui;

public:
	Lecture11_demo_custom_models(GeneRepository& r, QWidget *parent = 0);
	~Lecture11_demo_custom_models();

private:
	void setupTableView();
	void setupTreeView();
	void setupPaginatedTableView();
	void setupPictureTableView();
};

#endif // LECTURE11_DEMO_CUSTOM_MODELS_H
