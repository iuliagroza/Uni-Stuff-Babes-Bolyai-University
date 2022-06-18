#pragma once
#include <QDialog>
#include "ui_DialogGenesListWidget.h"
#include "GeneRepository.h"

using namespace genes;

class DialogGenesListWidget: public QDialog
{
private:
	Ui::DialogGenesWidget ui;
	GeneRepository& repo;

public:
	DialogGenesListWidget(GeneRepository& r, QWidget* parent = NULL);
	~DialogGenesListWidget();

	void populateList();
};

