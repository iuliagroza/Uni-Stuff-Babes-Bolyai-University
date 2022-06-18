#ifndef A11_12_IULIAGROZA_FILTERGUI_H
#define A11_12_IULIAGROZA_FILTERGUI_H

#include <QWidget>
#include <QListWidget>
#include "../controller/Controller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class FilterGUI; }
QT_END_NAMESPACE

class FilterGUI : public QWidget {
Q_OBJECT

public:
    explicit FilterGUI(Controller &ctrl, QWidget *parent = nullptr);

    ~FilterGUI() override;

private:
    Ui::FilterGUI *ui;
    Controller &ctrl;

    QListWidget *movies_list;
    QLineEdit* titleEdit;

    void handleFilter();
    void init();
    void populate_movies_list();
};


#endif
