#ifndef T3_IULIAGROZA_GUI_H
#define T3_IULIAGROZA_GUI_H

#include <QWidget>
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
    int totalTime;

    void populate();

    void filter();

    void handleFilter();

    void compute();

    void handleCompute();
};


#endif