#include "chatwindow.h"
#include "ui_ChatWindow.h"


ChatWindow::ChatWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::ChatWindow) {
    ui->setupUi(this);
}

ChatWindow::~ChatWindow() {
    delete ui;
}
