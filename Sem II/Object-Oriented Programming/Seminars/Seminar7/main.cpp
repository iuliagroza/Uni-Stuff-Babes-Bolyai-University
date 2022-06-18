#include <QApplication>
#include <QPushButton>
#include "chatwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ChatWindow chatWindow;
    chatWindow.show();
    return QApplication::exec();
}
