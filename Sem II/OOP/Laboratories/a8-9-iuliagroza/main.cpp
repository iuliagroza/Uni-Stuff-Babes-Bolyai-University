#include "ui/UI.h"
#include "repository/CSVUserRepository.h"
#include "repository/HTMLUserRepository.h"

/*
 * Main program
 */
int main() {
    std::string answer;
    while(true) {
        std::cout << "Please provide the type of file for the storage of your program data: (csv\\html)\n";
        std::cout << ">>> ";

        getline(std::cin, answer);

        if(answer != "csv" && answer != "html") {
            std::cout << "Invalid input.\n";
        } else {
            break;
        }
    }

    try {
        if (answer == "csv") {
            UserRepository *user_repo = new CSVUserRepository("../files/watchlist.csv");
            Controller ctrl = Controller("../files/movies.txt", user_repo);
            UI ui = UI(ctrl);
            ui.start();
        } else {
            UserRepository *user_repo = new HTMLUserRepository("../files/watchlist.html");
            Controller ctrl = Controller("../files/movies.txt", user_repo);
            UI ui = UI(ctrl);
            ui.start();
        }
    } catch(FileError &fe) {
        std::cout << fe.what() << "\n";
    }
    return 0;
}
