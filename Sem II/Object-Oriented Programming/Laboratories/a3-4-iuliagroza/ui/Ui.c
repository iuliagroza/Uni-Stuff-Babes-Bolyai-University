#include "Ui.h"
#include <string.h>
#include <time.h>

OfferRepo *(*filterByPrice_ptr)(OfferRepo*, double) = &filterByPrice;
OfferRepo *(*filterByDate_ptr)(OfferRepo*, Date) = &filterByDate;
OfferRepo *(*filterByType_ptr)(OfferRepo*, char*) = &filterByType;

UI *createUI(Controller *ctrl) {
    // Handling NULL/dangling pointers
    if (ctrl == NULL) {
        return NULL;
    }

    UI *ui = (UI *) malloc(sizeof(UI));
    // Handling NULL/dangling pointers
    if (ui == NULL) {
        return NULL;
    }

    ui->ctrl = ctrl;

    return ui;
}

void destroyUI(UI *ui) {
    // Handling NULL/dangling pointers
    if (ui == NULL) {
        return;
    }

    destroyController(ui->ctrl);
    free(ui);
}

void printMainMenu() {
    setbuf(stdout, 0);
    printf("Welcome to \"Happy Holidays\" Manager! Type the corresponding number of the chosen command:\n"
           "1. Add an offer\n"
           "2. Delete an offer\n"
           "3. Update an offer\n"
           "4. Display all offers whose destinations contain a given string and print them sorted ascending/descending by price.\n"
           "5. Display all offers of a given type, having their departure after a given date.\n"
           "6. Display all offers with a given maximum price.\n"
           "7. Undo the last operation.\n"
           "8. Redo the last operation.\n"
           "9. Exit\n");
}

/*
 * Checks if a number is in the range [x, y]
 * */
int inRange(int n, int x, int y) {
    int i;
    for (i = x; i <= y; i++) {
        if (n == i) {
            return 1;
        }
    }

    return 0;
}

/*
 * Gets the input of the main menu and validates it.
 * */
int getMainMenuInput() {
    int n = 0;
    char input[100];

    while (1) {
        printf(">>> ");
        scanf("%s", input);
        int check = sscanf(input, "%d", &n);
        if (check != 1 || inRange(n, 1, 9) == 0) {
            printf("Please provide a natural number between 1 and 8.\n");
        } else {
            break;
        }
    }

    return n;
}

/*
 * Checks if the type of an offer is "seaside", "mountain" or "city break".
 * */
int validateType(char *type) {
    if (strcmp(type, "seaside") == 0 || strcmp(type, "mountain") == 0 || strcmp(type, "city break") == 0) {
        return 1;
    }

    return 0;
}

/*
 * Gets the input of type of an offer and validates it.
 * */
char *getTypeInput(int new) {
    char *type = malloc(sizeof(char) * 100);

    while (1) {
        if (new) {
            printf("Please provide the new type of the offer (\"seaside\", \"mountain\", \"city break\"): ");
        } else {
            printf("Please provide the type of the offer (\"seaside\", \"mountain\", \"city break\"): ");
        }
        scanf(" %[^\n]", type);

        if (validateType(type) == 0) {
            printf("Invalid type.\n");
        } else {
            break;
        }
    }

    return type;
}

/*
 * Gets the input of destination of an offer and validates it.
 * */
char *getDestinationInput() {
    char *destination = malloc(sizeof(char) * 100);

    printf("Please provide the destination of the offer: ");
    scanf(" %[^\n]", destination);
    return destination;
}

/*
 * Gets the input of the year of the departureDate and validates it.
 * */
int getYearInput() {
    char s[100];
    int year = 0;

    while (1) {
        printf("Please provide the year of the departure: ");
        scanf(" %[^\n]", s);

        int check = sscanf(s, "%d", &year);

        if (check != 1 || inRange(year, 2022, 2100) == 0) {
            printf("Invalid year.\n");
        } else {
            int currentYear;
            time_t now = time(0);
            struct tm *local = gmtime(&now);
            currentYear = local->tm_year + 1900;

            if (year < currentYear) {
                printf("You must provide a future date.\n");
            } else {
                break;
            }
        }
    }

    return year;
}

/*
 * Gets the input of the month of the departureDate and validates it.
 * */
int getMonthInput(int year) {
    char s[100];
    int month = 0;

    while (1) {
        printf("Please provide the month of the departure (integer from 1 to 12): ");
        scanf("%s", s);

        int check = sscanf(s, "%d", &month);

        if (check != 1 || inRange(month, 1, 12) == 0) {
            printf("Invalid month.\n");
        } else {
            int currentMonth;
            int currentYear;
            time_t now = time(0);
            struct tm *local = gmtime(&now);
            currentMonth = local->tm_mon + 1;
            currentYear = local->tm_year + 1900;

            if (year == currentYear && month < currentMonth) {
                printf("You must provide a future date.\n");
            } else {
                break;
            }
        }
    }

    return month;
}

/*
 * Gets the input of the day of the departureDate and validates it.
 * */
int getDayInput(int month, int year) {
    char s[100];
    int day = 0;

    int lastDayOfMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 4 == 0) {
        lastDayOfMonth[2]++;
    }

    while (1) {
        printf("Please provide the day of the departure: ");
        scanf("%s", s);

        int check = sscanf(s, "%d", &day);

        if (check != 1 || inRange(day, 1, lastDayOfMonth[month]) == 0) {
            printf("Invalid day. Check what is the last day of the month you previously provided.\n");
        } else {
            int currentDay;
            int currentMonth;
            int currentYear;
            time_t now = time(0);
            struct tm *local = gmtime(&now);
            currentDay = local->tm_mday;
            currentMonth = local->tm_mon + 1;
            currentYear = local->tm_year + 1900;

            if (year == currentYear && month == currentMonth && day < currentDay) {
                printf("You must provide a future date.\n");
            } else {
                break;
            }
        }
    }

    return day;
}

/*
 * Gets the input of the departureDate of an offer and validates it.
 * */
Date getDateInput() {
    int year = getYearInput();
    int month = getMonthInput(year);
    int day = getDayInput(month, year);

    Date d;
    d.day = day;
    d.month = month;
    d.year = year;

    return d;
}

/*
 * Gets the input of the price of an offer and validates it.
 * */
double getPriceInput(int new) {
    char s[100];
    double price = 0;

    while (1) {
        if (new) {
            printf("Please provide the new price of the offer: ");
        } else {
            printf("Please provide the price of the offer: ");
        }
        scanf("%s", s);

        int check = sscanf(s, "%lf", &price);

        if (check != 1 || price < 0) {
            printf("Invalid price.\n");
        } else {
            break;
        }
    }

    return price;
}

void getAddInput(UI *ui) {
    char *type = getTypeInput(0);
    char *destination = getDestinationInput();
    Date departureDate = getDateInput();
    double price = getPriceInput(0);

    int ok = addController(ui->ctrl, type, destination, departureDate, price);

    if (ok) {
        printf("Offer successfully added.\n");
    } else {
        printf("The offer you provided already exists in the database.\n");
    }

    free(type);
    free(destination);
}

void getDeleteInput(UI *ui) {
    char *destination = getDestinationInput();
    Date departureDate = getDateInput();

    int ok = deleteController(ui->ctrl, destination, departureDate);

    if (ok) {
        printf("Offer successfully deleted.\n");
    } else {
        printf("The offer you provided does not exist in the database.\n");
    }

    free(destination);
}

void getUpdateInput(UI *ui) {
    char *destination = getDestinationInput();
    Date departureDate = getDateInput();
    char *newType = getTypeInput(1);
    double newPrice = getPriceInput(1);

    int ok = updateController(ui->ctrl, newType, destination, departureDate, newPrice);

    if (ok) {
        printf("Offer successfully updated.\n");
    } else {
        printf("The offer you provided does not exist in the database.\n");
    }

    free(destination);
    free(newType);
}

char *getPatternInput() {
    char *s = malloc(sizeof(char) * 100);
    printf("Please provide the keyword of the search; if you want to display all the offers, please type \"none\": ");
    scanf(" %[^\n]", s);

    return s;
}

int getSortInput() {
    char s[100];

    while (1) {
        printf("Please provide the sorting option (\"ascending\" or \"descending\"): ");
        scanf("%s", s);

        if (strcmp(s, "ascending") != 0 && strcmp(s, "descending") != 0) {
            printf("Invalid option.\n");
        } else {
            break;
        }
    }

    if (strcmp(s, "ascending") == 0) {
        return 1;
    }
    return 0;
}

void displayUI(UI *ui) {
    char *pattern = getPatternInput();
    if (strcmp(pattern, "none") == 0) {
        strcpy(pattern, "");
    }

    int sortOption = getSortInput();
    sort(ui->ctrl, sortOption);

    int count = 0;

    for (int i = 0; i < getSize(ui->ctrl->repo); i++) {
        if (strstr(getDestination(ui->ctrl->repo->offers->elements[i]), pattern) != NULL) {
            count++;
            printf("%d. ", count);
            toString(ui->ctrl->repo->offers->elements[i]);
        }
    }

    if (count == 0) {
        printf("No offers are matching.\n");
    }

    free(pattern);
}

void filterOne(UI *ui) {
    char *type = getTypeInput(0);
    Date departureDate = getDateInput();

    OfferRepo *newRepo = (*filterByType_ptr)(getRepo(ui->ctrl), type);
    newRepo = (*filterByDate_ptr)(newRepo, departureDate);

    if (getSize(newRepo) == 0) {
        printf("No offers are matching.\n");
    } else {
        for (int i = 0; i < getSize(newRepo); i++) {
            printf("%d. ", i + 1);
            toString(newRepo->offers->elements[i]);
        }
    }

    free(type);
    destroyRepo(newRepo);
}

void filterTwo(UI *ui) {
    double price = getPriceInput(0);

    OfferRepo *newRepo = (*filterByPrice_ptr)(getRepo(ui->ctrl), price);

    if (getSize(newRepo) == 0) {
        printf("No offers are matching.\n");
    } else {
        for (int i = 0; i < getSize(newRepo); i++) {
            printf("%d. ", i + 1);
            toString(newRepo->offers->elements[i]);
        }
    }

    destroyRepo(newRepo);
}

void run(UI *ui) {
    int out = 0;
    generateInstances(ui->ctrl);

    while (out == 0) {
        printMainMenu();

        int option = getMainMenuInput();
        int result = 0;

        switch (option) {
            case 1:
                getAddInput(ui);
                break;
            case 2:
                getDeleteInput(ui);
                break;
            case 3:
                getUpdateInput(ui);
                break;
            case 4:
                displayUI(ui);
                break;
            case 5:
                filterOne(ui);
                break;
            case 6:
                filterTwo(ui);
                break;
            case 7:
                result = undo(ui->ctrl);
                if (result == 0) {
                    printf("There are no more operations to undo!\n");
                }
                break;
            case 8:
                result = redo(ui->ctrl);
                if (result == 0) {
                    printf("There are no more operations to redo!\n");
                }
                break;
            case 9:
                out = 1;
                break;
            default:
                break;
        }
    }
}
