#include <QApplication>
#include <QWindow>
#include "repository/CSVUserRepository.h"
#include "gui/filtergui.h"
#include "gui/maingui.h"
#include "gui/modeadmingui.h"
#include "gui/modeusergui.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    UserRepository *user_repo = new CSVUserRepository("../files/watchlist.csv");
    Controller ctrl = Controller("../files/movies.txt", user_repo);

    ModeAdminGUI adminGui(ctrl);
    adminGui.show();

    FilterGUI filterGui(ctrl);
    filterGui.show();

    MainGUI mainGui;
    mainGui.show();

    ModeUserGUI userGui;
    userGui.show();
    return QApplication::exec();
}
