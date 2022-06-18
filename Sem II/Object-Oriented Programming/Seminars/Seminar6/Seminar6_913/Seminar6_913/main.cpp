#include "Seminar6_913.h"
#include <QtWidgets/QApplication>
#include "TeachersWindow.h"
#include <memory>
#include "StudentsModel.h"
#include <QSortFilterProxyModel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Repository repo{"Students.txt"};
    //auto model = std::make_unique<StudentsModel>(repo);
    auto model = new StudentsModel{ repo };

    auto mainTeacherWnd = std::make_unique<TeachersWindow>(model);
    mainTeacherWnd->setWindowTitle("Main teacher");
    mainTeacherWnd->show();

    //auto proxyModel = std::make_unique<QSortFilterProxyModel>();
    auto proxyModel = new QSortFilterProxyModel{};
    proxyModel->setSourceModel(model);
    proxyModel->setFilterKeyColumn(1);
    proxyModel->setFilterRegularExpression(QRegularExpression{"913"});
    auto teacherFor913Wnd = std::make_unique<TeachersWindow>(proxyModel);
    teacherFor913Wnd->setWindowTitle("Teacher for 913");
    teacherFor913Wnd->show();

    return a.exec();
}
