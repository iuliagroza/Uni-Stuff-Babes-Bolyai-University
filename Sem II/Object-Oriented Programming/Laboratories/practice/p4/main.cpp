#include <QApplication>
#include <QPushButton>
#include "Service.h"
#include "userwidget.h"
#include "Tests.h"

int main(int argc, char *argv[]) {
    Tests::testAdd();
    Tests::testUpdate();

    QApplication a(argc, argv);
    Service s;
    s.sortIssues();
    std::vector<UserWidget> list;

    int index = 0;

    for (auto& i : s.getUsers())
    {
        UserWidget *u = new UserWidget(s);
        u->setWindowTitle(QString::fromStdString(i.getName()) + ' ' + QString::fromStdString(i.getType()));

        // check whether solve button should be disabled or not
        //u->check();

        u->show();
    }
    return QApplication::exec();
}
