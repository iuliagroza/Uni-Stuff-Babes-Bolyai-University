#include <QApplication>
#include <QPushButton>
#include "window.h"
#include "Service.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repository repository;
    Service service(repository);
    for(auto &user : service.get_users()) {
        Window window(service);
        window.setWindowTitle(QString::fromStdString(user.get_name() + " " + user.get_type()));
        window.show();
    }
    return QApplication::exec();
}
