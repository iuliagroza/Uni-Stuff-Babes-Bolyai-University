#include "window.h"
#include "ui_Window.h"


Window::Window(Service& service, QWidget *parent) :
        QWidget(parent), ui(new Ui::Window), service(service) {
    ui->setupUi(this);
}

Window::~Window() {
    delete ui;
}
