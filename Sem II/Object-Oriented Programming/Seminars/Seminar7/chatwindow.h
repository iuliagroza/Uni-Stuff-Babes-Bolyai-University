#ifndef SEMINAR7_CHATWINDOW_H
#define SEMINAR7_CHATWINDOW_H

#include <QWidget>
#include "Observer.h"
#include "ChatSession.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ChatWindow; }
QT_END_NAMESPACE

class ChatWindow : public QWidget, public Observer {
Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);

    ~ChatWindow() override;

private:
    Ui::ChatWindow *ui;
    std::vector<std::string> users;
    std::vector<ChatSession> chatSessions;

    void update() override;
};


#endif
