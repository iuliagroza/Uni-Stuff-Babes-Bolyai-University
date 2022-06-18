#ifndef P1_GUI_H
#define P1_GUI_H

#include <QWidget>
#include <QListWidget>
#include "Controller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QWidget {
Q_OBJECT

public:
    explicit gui(Controller &ctrl, QWidget *parent = nullptr);

    ~gui() override;

private:
    Ui::gui *ui;
    Controller &ctrl;

    void populate();
};


#endif
