#include "gui.h"
#include "ui_gui.h"


gui::gui(Controller &ctrl, QWidget *parent) :
        QWidget(parent), ui(new Ui::gui), ctrl(ctrl) {
    ui->setupUi(this);
    this->populate();
}

gui::~gui() {
    delete ui;
}

void gui::populate() {
    this->ui->listWidget->clear();

    for(auto &t: this->ctrl.get_tasks()) {
        this->ui->listWidget->addItem(QString::fromStdString(t.to_string()));

        if(t.get_priority() == 1) {
            QFont font{"Verdana", 14};
            font.setWeight(QFont::ExtraBold);
            font.setPixelSize(14);
            //this->ui->listWidget->currentItem()->setFont(font);
        }
    }
}
