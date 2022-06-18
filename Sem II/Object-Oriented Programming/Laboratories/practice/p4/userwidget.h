#ifndef UNTITLED1_USERWIDGET_H
#define UNTITLED1_USERWIDGET_H

#include <QWidget>
#include "Service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class UserWidget; }
QT_END_NAMESPACE

class UserWidget : public QWidget, public Observer {
Q_OBJECT

public:
    explicit UserWidget(Service& srv, QWidget *parent = nullptr);

    ~UserWidget() override;
    void update() override;
    void check();

private:
    Ui::UserWidget *ui;
    Service& srv;

    void addIssueHandler();
    void removeIssueHandler();
    void resolveIssueHandler();
    void connectSignalsAndSlots();
    void populateIssues();
};


#endif
