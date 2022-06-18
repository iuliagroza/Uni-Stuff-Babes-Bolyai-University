#ifndef A11_12_IULIAGROZA_USERGUI_H
#define A11_12_IULIAGROZA_USERGUI_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include "../controller/Controller.h"
#include "../validators/Validators.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ModeAdminGUI; }
QT_END_NAMESPACE

class ModeAdminGUI : public QWidget {
Q_OBJECT

public:
    explicit ModeAdminGUI(Controller &ctrl, QWidget *parent = nullptr);

    ~ModeAdminGUI() override;

private:
    Ui::ModeAdminGUI *ui;
    Controller &ctrl;
    Validators validator;

    QListWidget *movies_list;

    QListWidget* playList;
    QLineEdit* titleEdit;
    QLineEdit* genreEdit;
    QLineEdit* yearEdit;
    QLineEdit* numberOfLikesEdit;
    QLineEdit* trailerEdit;
    QPushButton* addMovieButton;
    QPushButton* deleteMovieButton;
    QPushButton* updateMovieButton;
    QPushButton* filterMovieButton;
    QPushButton* playlistButton;
    QPushButton* playButton;
    QPushButton* nextButton;
    QLabel *valid;


    void handleHide();
    void handleAddButton();
    void handleRemoveButton();
    void handleUpdateButton();
    void handleFilter();
    void init();
    void populate_movies_list();
    bool validateInput(std::string title, std::string genre, std::string year, std::string likes, std::string trailer);
};


#endif
