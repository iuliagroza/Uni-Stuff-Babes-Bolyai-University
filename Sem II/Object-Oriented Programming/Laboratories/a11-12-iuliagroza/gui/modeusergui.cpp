//
// Created by groza on 5/18/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ModeUserGUI.h" resolved

#include "modeusergui.h"
#include "ui_ModeUserGUI.h"


ModeUserGUI::ModeUserGUI(QWidget *parent) :
        QWidget(parent), ui(new Ui::ModeUserGUI) {
    ui->setupUi(this);
}

ModeUserGUI::~ModeUserGUI() {
    delete ui;
}
