#include "QtWidgetsApplication2.h"
#include <QtWidgets/QApplication>
#include "UsersGUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UsersGUI w;
    w.show();
    return a.exec();
}
