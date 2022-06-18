//
// Created by groza on 5/15/2022.
//

#ifndef A11_12_IULIAGROZA_MAINGUI_H
#define A11_12_IULIAGROZA_MAINGUI_H

#include <QWidget>
#include <QPushButton>


QT_BEGIN_NAMESPACE
namespace Ui { class MainGUI; }
QT_END_NAMESPACE

class MainGUI : public QWidget {
Q_OBJECT

public:
    explicit MainGUI(QWidget *parent = nullptr);

    ~MainGUI() override;

private:
    Ui::MainGUI *ui;

    void init();
};


#endif
