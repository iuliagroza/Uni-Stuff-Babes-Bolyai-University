#ifndef A11_12_IULIAGROZA_MODEUSERGUI_H
#define A11_12_IULIAGROZA_MODEUSERGUI_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class ModeUserGUI; }
QT_END_NAMESPACE

class ModeUserGUI : public QWidget {
Q_OBJECT

public:
    explicit ModeUserGUI(QWidget *parent = nullptr);

    ~ModeUserGUI() override;

private:
    Ui::ModeUserGUI *ui;
};


#endif
