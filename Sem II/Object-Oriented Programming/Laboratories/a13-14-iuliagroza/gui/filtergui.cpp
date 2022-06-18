#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QObject>
#include <QFormLayout>
#include <QPushButton>
#include "filtergui.h"
#include "ui_FilterGUI.h"


FilterGUI::FilterGUI(Controller &ctrl, QWidget *parent) :
        QWidget(parent), ui(new Ui::FilterGUI), ctrl(ctrl) {
    ui->setupUi(this);
    this->init();
    this->populate_movies_list();
}

FilterGUI::~FilterGUI() {
    delete ui;
}

void FilterGUI::handleFilter() {
    std::string pattern = this->titleEdit->text().toStdString();
    this->movies_list->clear();
    std::vector<Movie> movies = this->ctrl.get_admin_repo().get_movies();

    for(auto &m : movies) {
        std::string source = m.to_str();

        std::for_each(source.begin(), source.end(), [](char & c) {
            c = ::tolower(c);
        });

        if(source.find(pattern) != std::string::npos) {
            this->movies_list->addItem(QString::fromStdString(m.to_str()));
        }
    }
}

void FilterGUI::init() {
    auto* layout = new QHBoxLayout{ this };
    /// -----------------------LIST
    this->movies_list = new QListWidget{};
    QLinearGradient grad(0,0,0, this->movies_list->height());
    grad.setColorAt(1, Qt::white);
    grad.setColorAt(0, Qt::blue);
    QPalette pal = this->movies_list->palette();
    pal.setBrush(QPalette::ColorRole::Base, QBrush(grad));
    this->movies_list->setPalette(pal);
    this->movies_list->setSelectionMode(QAbstractItemView::SingleSelection);
    auto* allSongsLabel = new QLabel{ "All movies" };
    auto* leftSide = new QWidget{};
    auto* leftLayout = new QVBoxLayout{leftSide};

    leftLayout->addWidget(allSongsLabel);
    leftLayout->addWidget(this->movies_list);

    /// -----------------------MOVIE DATA
    auto* formLayout = new QWidget{};
    auto* movieLayout = new QFormLayout{ formLayout };

    this->titleEdit = new QLineEdit{};
    QFont f{ "Verdana", 10 };
    auto* titleLabel = new QLabel{ "&Search " };
    titleLabel->setBuddy(this->titleEdit);
    titleLabel->setFont(f);
    this->titleEdit->setFont(f);
    movieLayout->addRow(titleLabel, this->titleEdit);

    leftLayout->addWidget(formLayout);
    ///----------------------- BUTTONS

    auto* buttonsWidget = new QWidget{};
    QPushButton::connect(this->titleEdit, &QLineEdit::textChanged, this, &FilterGUI::handleFilter);

    leftLayout->addWidget(buttonsWidget);
    layout->addWidget(leftSide);
}

void FilterGUI::populate_movies_list() {
    this->movies_list->clear();
    std::vector<Movie> movies = this->ctrl.get_admin_repo().get_movies();

    for(auto &m : movies) {
        this->movies_list->addItem(QString::fromStdString(m.to_str()));
    }
}
