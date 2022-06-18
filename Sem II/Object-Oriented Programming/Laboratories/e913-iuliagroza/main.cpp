#include <QApplication>
#include <QPushButton>
#include "window.h"
#include "Repository.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repository r;
    Service s;
    s.sort();

    Window *u_presenter = new Window(0, s);
    u_presenter->setWindowTitle("Presenter");
    u_presenter->show();

    for (auto& i : s.getParticipants())
    {
        Window *u = new Window(1, s);
        u->setWindowTitle(QString::fromStdString(i.getName()));

        // check whether solve button should be disabled or not
        //u->check();

        u->show();
    }
    s.writeToFile();
    return QApplication::exec();
}
