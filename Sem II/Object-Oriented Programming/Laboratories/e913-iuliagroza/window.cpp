#include <QMessageBox>
#include "window.h"
#include "ui_Window.h"


Window::Window(int type, Service& srv, QWidget *parent) :
        QWidget(parent), ui(new Ui::Window), srv(srv), type(type) {
    ui->setupUi(this);
    this->connectSignalsAndSlots();
    this->srv.addObserver(this);
    this->populateQuestions();
    if(this->type == 1) {
        this->ui->score_listWidget->clear();
        this->ui->score_listWidget->addItem("0");
    }
}

Window::~Window() {
    delete ui;
}

void Window::update()
{
    this->populateQuestions();
}

bool cmp2(Question& q1, Question& q2) {
    return (q1.getScore() > q2.getScore());
}

void Window::populateQuestions()
{
    this->ui->listWidget->clear();

    if(this->type == 0) {
        this->srv.sort();
        for (auto& i : this->srv.getQuestions())
        {
            this->ui->listWidget->addItem(QString::fromStdString(std::to_string(i.getId())) + ',' + QString::fromStdString(i.getText()) + ',' + QString::fromStdString(i.getAnswer()) + ',' + QString::fromStdString(std::to_string(i.getScore())));
        }
    } else {
        std::sort(this->srv.getQuestions().begin(), this->srv.getQuestions().end(), cmp2);
        for (auto& i : this->srv.getQuestions()) {
            auto *item = new QListWidgetItem(QString::fromStdString(std::to_string(i.getId())) + ',' + QString::fromStdString(i.getText()) + ',' + QString::fromStdString(std::to_string(i.getScore())));
            std::string answer, name;

            std::stringstream x(this->windowTitle().toStdString());

            std::getline(x, name);
            for(auto &p : this->srv.getParticipants()) {
                if(p.getName() == name) {
                    for(auto &ans : p.getAnswered()) {
                        if (i.getId() == ans) {
                            QBrush brush{QColor{80, 220, 100}};
                            item->setBackground(brush);
                        }
                    }
                }
            }
            this->ui->listWidget->addItem(item);
        }
    }
}

void Window::addHandler()
{
    int id;
    std::string text, answer;
    std::string id_s;
    int score = 100;

    if (this->type == 0)
    {

        id = ui->id_lineEdit->text().toInt();

        std::string id_s = ui->id_lineEdit->text().toStdString();

        if (id_s.empty()) {
            QMessageBox::critical(0, "Error", "Id cannot be empty!");
            return;
        }

        for (auto& i : this->srv.getQuestions())
        {
            if (i.getId() == id)
            {
                QMessageBox::critical(0, "Error", "Question with same id already exists!");
                return;
            }
        }

        text = ui->text_lineEdit->text().toStdString();

        if (text.empty()) {
            QMessageBox::critical(0, "Error", "Text cannot be empty!");
            return;
        }

        answer = ui->answer_lineEdit->text().toStdString();

        if (answer.empty()) {
            QMessageBox::critical(0, "Error", "Answer cannot be empty!");
            return;
        }

        score = ui->score_lineEdit->text().toInt();

        std::string score_s = ui->score_lineEdit->text().toStdString();

        if (score_s.empty()) {
            QMessageBox::critical(0, "Error", "Score cannot be empty!");
            return;
        }

        Question q(id, text, answer, score);
        this->srv.addQuestion(q);

        this->populateQuestions();
        this->srv.writeToFile();
    }
    else
        this->ui->addButton->setDisabled(true);
}

void Window::answerHandler()
{
    int id;
    std::string answer, name;

    std::stringstream x(this->windowTitle().toStdString());

    std::getline(x, name);

    if (this->type == 1)
    {

        id = ui->id_user_lineEdit->text().toInt();

        answer = ui->answer_user_lineEdit->text().toStdString();

        int score = 0;

        bool ok=0;
        for(auto &q: this->srv.getParticipants()) {
            for(auto &a : q.getAnswered()) {
                if(a == id) {
                    this->ui->answerButton->setDisabled(true);
                    ok=1;
                }
            }
        }
        if(ok==0) {
            for (auto &q: this->srv.getQuestions()) {
                if (q.getId() == id) {
                    if (q.getAnswer() == answer) {
                        score = q.getScore();
                    }
                }
            }

            if (score != 0) {
                for (auto &p: this->srv.getParticipants()) {
                    if (name == p.getName()) {
                        p.setScore(p.getScore() + score);
                        p.getAnswered().push_back(id);
                        this->ui->score_listWidget->clear();
                        this->ui->score_listWidget->addItem(QString::fromStdString(std::to_string(p.getScore())));
                        this->populateQuestions();
                    }
                }
            }
        }
    }
    else
        this->ui->answerButton->setDisabled(true);
}

void Window::connectSignalsAndSlots()
{
    QObject::connect(this->ui->addButton, &QPushButton::clicked, this, &Window::addHandler);
    QObject::connect(this->ui->answerButton, &QPushButton::clicked, this, &Window::answerHandler);
}