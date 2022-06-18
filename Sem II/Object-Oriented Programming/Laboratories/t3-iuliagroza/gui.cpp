#include <QObject>
#include "gui.h"
#include "ui_gui.h"
#include <cmath>


gui::gui(Controller &ctrl, QWidget *parent) :
        QWidget(parent), ui(new Ui::gui), ctrl(ctrl) {
    ui->setupUi(this);
    this->totalTime = 0;
    this->populate();
    this->filter();
    this->compute();
}

gui::~gui() {
    delete ui;
}

void gui::handleFilter() {
    int pattern = this->ui->lineEdit->text().toInt();
    this->ui->listWidget->clear();
    std::vector<Interval> intervals = this->ctrl.get_intervals();

    for(auto &i : intervals) {
        if(i.get_precipitation()< pattern || pattern==0) {
            this->ui->listWidget->addItem(QString::fromStdString(i.to_string()));
        }
    }
}

void gui::filter() {
    QObject::connect(this->ui->lineEdit, &QLineEdit::textChanged, this, &gui::handleFilter);
}

void gui::handleCompute() {
    std::string description = this->ui->lineEdit_2->text().toStdString();
    int start_time = this->ui->lineEdit_3->text().toInt();

    this->totalTime = 0;

    std::vector<Interval> intervals = this->ctrl.get_intervals();

    for(auto &i : intervals) {
        if(i.get_description() == description && i.get_end_time() >= start_time) {
            int time = i.get_end_time() - std::max(i.get_start_time(), start_time);
            this->totalTime += time;
        }
    }

    this->ui->listWidget_2->clear();
    std::string res;
    if(this->totalTime == 0) {
        res += "There are no such intervals.";
    } else {
        res += "Total number of hours: " + std::to_string(this->totalTime);
    }
    this->ui->listWidget_2->addItem(QString::fromStdString(res));
}

void gui::compute() {
    QPushButton::connect(this->ui->pushButton, &QPushButton::clicked, this, &gui::handleCompute);
}

void gui::populate() {
    this->ui->listWidget->clear();

    for(auto &t: this->ctrl.get_intervals()) {
        this->ui->listWidget->addItem(QString::fromStdString(t.to_string()));
    }
}
