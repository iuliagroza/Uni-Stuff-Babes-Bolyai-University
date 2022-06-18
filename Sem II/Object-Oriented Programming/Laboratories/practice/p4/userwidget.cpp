#include <QMessageBox>
#include "userwidget.h"
#include "ui_UserWidget.h"


UserWidget::UserWidget(Service& srv, QWidget *parent) :
        QWidget(parent), ui(new Ui::UserWidget), srv(srv) {
    ui->setupUi(this);
    this->connectSignalsAndSlots();
    this->srv.addObserver(this);
    this->populateIssues();
}

UserWidget::~UserWidget() {
    delete ui;
}

void UserWidget::update()
{
    this->populateIssues();
}

void UserWidget::check()
{
    // get window title
    std::stringstream x(this->windowTitle().toStdString());

    std::string solver, userType;
    // set reporter of issue
    std::getline(x, solver, ' ');
    // set type of reporter of issue
    std::getline(x, userType, '\n');
    if (userType == "Tester")
        this->ui->resolveButton->setDisabled(true);
}

void UserWidget::addIssueHandler()
{
    std::string desc;
    std::string reporter, userType;

    // get window title
    std::stringstream x(this->windowTitle().toStdString());

    // set reporter of issue
    std::getline(x, reporter, ' ');
    // set type of reporter of issue
    std::getline(x, userType, '\n');

    if (userType == "tester")
    {

        desc = ui->issueDescLineEdit->text().toStdString();

        for (auto& i : this->srv.getIssues())
        {
            if (i.getDescription() == desc)
            {
                QMessageBox::critical(0, "Error", "Issue with same description already exists!");
                return;
            }
        }

        if (desc.empty()) {
            QMessageBox::critical(0, "Error", "Description cannot be empty!");
            return;
        }

        Issue i(desc, "open", reporter, "empty");
        this->srv.addIssue(i);

        this->populateIssues();
        this->srv.writeIssuesToFile();
    }
    else
        this->ui->addIssueButton->setDisabled(true);
}

void UserWidget::removeIssueHandler()
{
    std::stringstream x(ui->listWidget->currentItem()->text().toStdString());

    std::string desc, status, reporter, solver;

    std::getline(x, desc, ',');
    std::getline(x, status, ',');
    std::getline(x, reporter, ',');
    std::getline(x, solver, '\n');

    if (status == "open")
        this->ui->removeIssueButton->setDisabled(true);

    if (status == "closed")
    {
        Issue i{ desc, status, reporter, solver };

        this->srv.removeIssue(i);
        this->populateIssues();
        this->srv.writeIssuesToFile();

    }
}

void UserWidget::resolveIssueHandler()
{

    std::stringstream x(ui->listWidget->currentItem()->text().toStdString());

    std::string desc, status, reporter, solver;

    std::getline(x, desc, ',');
    std::getline(x, status, ',');
    std::getline(x, reporter, ',');
    std::getline(x, solver, '\n');

    std::stringstream aux(this->windowTitle().toStdString());

    std::string userType;
    std::getline(aux, solver, ' ');
    std::getline(aux, userType, '\n');

    if (userType == "programmer")
    {
        if (status == "closed")
            this->ui->resolveButton->setDisabled(true);

        if (status == "open")
        {
            this->srv.updateIssue(desc, "closed", reporter, solver);
            this->populateIssues();
            this->srv.writeIssuesToFile();
        }
    }
}

void UserWidget::connectSignalsAndSlots()
{
    QObject::connect(this->ui->addIssueButton, &QPushButton::clicked, this, &UserWidget::addIssueHandler);
    QObject::connect(this->ui->removeIssueButton, &QPushButton::clicked, this, &UserWidget::removeIssueHandler);
    QObject::connect(this->ui->resolveButton, &QPushButton::clicked, this, &UserWidget::resolveIssueHandler);
}

void UserWidget::populateIssues()
{
    this->ui->listWidget->clear();

    for (auto& i : this->srv.getIssues())
    {
        this->ui->listWidget->addItem(QString::fromStdString(i.getDescription()) + ',' + QString::fromStdString(i.getStatus()) + ',' + QString::fromStdString(i.getReporter()) + ',' + QString::fromStdString(i.getSolver()));
    }
}
