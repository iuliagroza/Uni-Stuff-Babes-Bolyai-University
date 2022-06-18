#include <QLabel>
#include <QHBoxLayout>
#include <QFormLayout>
#include "modeadmingui.h"
#include "ui_ModeAdminGUI.h"
#include "filtergui.h"


ModeAdminGUI::ModeAdminGUI(Controller &ctrl, QWidget *parent) :
        QWidget(parent), ui(new Ui::ModeAdminGUI), ctrl(ctrl) {
    ui->setupUi(this);
    this->init();
    this->populate_movies_list();
}

ModeAdminGUI::~ModeAdminGUI() {
    delete ui;
}

bool validateTrailer(std::string trailer) {
    return trailer!="";
}

bool ModeAdminGUI::validateInput(std::string title, std::string genre, std::string year, std::string likes, std::string trailer) {
    return (title!="") && (genre!="") && (trailer!="") && (this->validator.is_number(year)) &&
    (stoi(year) >= 1900) && (stoi(year) <= 2022) && (this->validator.is_number(likes));
}

void ModeAdminGUI::handleHide() {
    this->valid->hide();
}

void ModeAdminGUI::handleAddButton() {
    std::string title = this->titleEdit->text().toStdString();
    std::string genre = this->genreEdit->text().toStdString();
    std::string trailer = this->trailerEdit->text().toStdString();
    std::string number_of_likes = this->numberOfLikesEdit->text().toStdString();
    std::string year_of_release = this->yearEdit->text().toStdString();

    if(this->validateInput(title, genre, year_of_release, number_of_likes, trailer)) {
        Movie m = Movie(title, genre, stoi(year_of_release), stoi(number_of_likes), trailer);

        try {
            this->ctrl.add_admin(m);
            this->populate_movies_list();
        } catch(OperationError &oe) {
            this->valid->show();
        }
    } else {
        this->valid->show();
    }
}

void ModeAdminGUI::handleRemoveButton() {
    std::string trailer = this->trailerEdit->text().toStdString();
    if(validateTrailer(trailer)) {
        Movie m = Movie("", "", 2022, 0, trailer);

        try {
            this->ctrl.remove_admin(m);
            this->populate_movies_list();
        } catch(OperationError &oe) {
            this->valid->show();
        }
    } else {
        this->valid->show();
    }
}

void ModeAdminGUI::handleUpdateButton() {
    std::string title = this->titleEdit->text().toStdString();
    std::string genre = this->genreEdit->text().toStdString();
    std::string trailer = this->trailerEdit->text().toStdString();
    std::string number_of_likes = this->numberOfLikesEdit->text().toStdString();
    std::string year_of_release = this->yearEdit->text().toStdString();

    if(this->validateInput(title, genre, year_of_release, number_of_likes, trailer)) {
        Movie m = Movie("", "", 2022, 0, trailer);
        Movie new_m = Movie(title, genre, stoi(year_of_release), stoi(number_of_likes), trailer);

        try {
            this->ctrl.update_admin(m, new_m);
            this->populate_movies_list();
        } catch(OperationError &oe) {
            this->valid->show();
        }
    } else {
        this->valid->show();
    }
}

void ModeAdminGUI::handleFilter() {
    FilterGUI filterGui(this->ctrl);
    filterGui.show();
}

void ModeAdminGUI::init() {
    auto* layout = new QHBoxLayout{ this };
    /// ------------------------------- LEFT SIDE
    /// -----------------------LIST
    this->movies_list = new QListWidget{};
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
    this->genreEdit = new QLineEdit{};
    this->yearEdit = new QLineEdit{};
    this->numberOfLikesEdit = new QLineEdit{};
    this->trailerEdit = new QLineEdit{};
    QFont f{ "Verdana", 10 };
    auto* titleLabel = new QLabel{ "&Title:" };
    titleLabel->setBuddy(this->titleEdit);
    auto* genreLabel = new QLabel{ "&Genre:" };
    genreLabel->setBuddy(this->genreEdit);
    auto* yearLabel = new QLabel{ "&Year of release:" };
    yearLabel->setBuddy(this->yearEdit);
    auto* numberOfLikesLabel = new QLabel{ "&Number of likes:" };
    numberOfLikesLabel->setBuddy(this->numberOfLikesEdit);
    auto* trailerLabel = new QLabel{ "&Trailer:" };
    trailerLabel->setBuddy(this->trailerEdit);
    this->titleEdit->setFont(f);
    this->genreEdit->setFont(f);
    this->yearEdit->setFont(f);
    this->numberOfLikesEdit->setFont(f);
    this->trailerEdit->setFont(f);
    movieLayout->addRow(titleLabel, this->titleEdit);
    movieLayout->addRow(genreLabel, this->genreEdit);
    movieLayout->addRow(yearLabel, this->yearEdit);
    movieLayout->addRow(numberOfLikesLabel, this->numberOfLikesEdit);
    movieLayout->addRow(trailerLabel, this->trailerEdit);

    QLineEdit::connect(this->titleEdit, &QLineEdit::textChanged, this, &ModeAdminGUI::handleHide);
    QLineEdit::connect(this->genreEdit, &QLineEdit::textChanged, this, &ModeAdminGUI::handleHide);
    QLineEdit::connect(this->yearEdit, &QLineEdit::textChanged, this, &ModeAdminGUI::handleHide);
    QLineEdit::connect(this->numberOfLikesEdit, &QLineEdit::textChanged, this, &ModeAdminGUI::handleHide);
    QLineEdit::connect(this->trailerEdit, &QLineEdit::textChanged, this, &ModeAdminGUI::handleHide);

    leftLayout->addWidget(formLayout);
    ///----------------------- BUTTONS

    auto* buttonsWidget = new QWidget{};
    auto* gridLayout = new QGridLayout{buttonsWidget};

    this->addMovieButton = new QPushButton("Add");
    this->addMovieButton->setFont(f);
    QPushButton::connect(this->addMovieButton, &QPushButton::clicked, this, &ModeAdminGUI::handleAddButton);

    this->deleteMovieButton = new QPushButton("Remove");
    this->deleteMovieButton->setFont(f);
    QPushButton::connect(this->deleteMovieButton, &QPushButton::clicked, this, &ModeAdminGUI::handleRemoveButton);

    this->updateMovieButton = new QPushButton("Update");
    this->updateMovieButton->setFont(f);
    QPushButton::connect(this->updateMovieButton, &QPushButton::clicked, this, &ModeAdminGUI::handleUpdateButton);

    this->filterMovieButton = new QPushButton("Filter");
    this->filterMovieButton->setFont(f);
    QPushButton::connect(this->filterMovieButton, &QPushButton::clicked, this, &ModeAdminGUI::handleFilter);

    this->valid = new QLabel{ "Invalid input!" };
    this->valid->setFont(f);
    this->valid->hide();

    gridLayout->addWidget(this->addMovieButton, 0, 0);
    gridLayout->addWidget(this->deleteMovieButton, 0, 1);
    gridLayout->addWidget(this->updateMovieButton, 0, 2);
    gridLayout->addWidget(this->filterMovieButton, 1, 1);
    gridLayout->addWidget(this->valid, 2, 1);

    leftLayout->addWidget(buttonsWidget);

    ///------------------------------- MID SIDE

    auto* middleSide = new QWidget{};
    auto* middleLayout = new QVBoxLayout{middleSide};

    this->playlistButton = new QPushButton(">");
    this->playlistButton->setFont(f);

    middleLayout->addWidget(this->playlistButton);


    ///------------------------------- RIGHT SIDE

    auto* rightSide = new QWidget{};
    auto* rightLayout = new QVBoxLayout{rightSide};

    this->playList = new QListWidget{};
    this->playList->setSelectionMode(QAbstractItemView::SingleSelection);
    auto* playlistLabel = new QLabel{ "Playlist" };

    rightLayout->addWidget(playlistLabel);
    rightLayout->addWidget(this->playList);

    auto* buttonsPlaylist = new QWidget{};
    auto* gridPlaylist = new QGridLayout{buttonsPlaylist};

    this->playButton = new QPushButton("Play");
    this->playButton->setFont(f);
    this->nextButton = new QPushButton("Next");
    this->nextButton->setFont(f);

    gridPlaylist->addWidget(this->playButton, 0, 0);
    gridPlaylist->addWidget(this->nextButton, 0, 1);



    rightLayout->addWidget(buttonsPlaylist);


    /// ------------------------------- ADD ALL
    layout->addWidget(leftSide);
    //layout->addWidget(middleSide);
    //layout->addWidget(rightSide);
}

void ModeAdminGUI::populate_movies_list() {
    this->movies_list->clear();
    std::vector<Movie> movies = this->ctrl.get_admin_repo().get_movies();

    for(auto &m : movies) {
        this->movies_list->addItem(QString::fromStdString(m.to_str()));
    }
}
