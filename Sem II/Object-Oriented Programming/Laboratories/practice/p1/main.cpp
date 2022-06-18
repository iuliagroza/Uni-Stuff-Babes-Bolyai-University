#include <QApplication>
#include <QPushButton>
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Controller ctrl;
    gui gui(ctrl);
    gui.show();
    return QApplication::exec();
}
