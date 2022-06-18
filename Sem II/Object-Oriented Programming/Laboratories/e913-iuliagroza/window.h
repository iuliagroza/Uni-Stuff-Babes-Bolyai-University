#ifndef E913_IULIAGROZA_WINDOW_H
#define E913_IULIAGROZA_WINDOW_H

#include <QWidget>
#include "Observer.h"
#include "Service.h"
#include <algorithm>


QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QWidget, public Observer {
Q_OBJECT

public:
    explicit Window(int type, Service& srv, QWidget *parent = nullptr);

    ~Window() override;
    void update() override;

private:
    Ui::Window *ui;
    Service& srv;
    int type;

    void populateQuestions();
    void addHandler();
    void answerHandler();
    void connectSignalsAndSlots();
};


#endif
