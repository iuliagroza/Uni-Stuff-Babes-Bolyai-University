#pragma once
#include <QDialog>
#include "ui_DialogGenesListView.h"
#include "GeneRepository.h"

class DialogGenesView :
	public QDialog
{
private:
	GeneRepository& repo;
	Ui::DialogGenesListView ui;

public:
	DialogGenesView(GeneRepository& r, QWidget* parent = NULL);
	~DialogGenesView();
};

