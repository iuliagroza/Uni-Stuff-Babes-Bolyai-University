#ifndef P3_WINDOW_H
#define P3_WINDOW_H

#include <QWidget>
#include "Service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QWidget {
Q_OBJECT

public:
    explicit Window(Service& service, QWidget *parent = nullptr);

    ~Window() override;

private:
    Ui::Window *ui;
    Service& service;
};


#endif
