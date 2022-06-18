#include "maingui.h"
#include "ui_MainGUI.h"
#include "../repository/UserRepository.h"
#include "../repository/CSVUserRepository.h"
#include "../controller/Controller.h"


MainGUI::MainGUI(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainGUI) {
    ui->setupUi(this);
}

MainGUI::~MainGUI() {
    delete ui;
}
