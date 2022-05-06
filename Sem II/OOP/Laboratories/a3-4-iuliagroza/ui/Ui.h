#ifndef A3_4_IULIAGROZA_UI_H
#define A3_4_IULIAGROZA_UI_H

#include "../controller/Controller.h"

/*
 * Struct that stores the UI information.
 * */
typedef struct {
    Controller *ctrl;
} UI;

/*
 * Function that creates a UI object and allocates memory for it and implicitly for its fields.
 * return: pointer to a UI object containing the Controller object.
 * */
UI *createUI(Controller *ctrl);

/*
 * Function that destroys a UI object and deallocates its memory and implicitly its fields.
 * :ui: pointer to a UI object
 * */
void destroyUI(UI *ui);

/*
 * Main function
 * */
void run(UI *ui);

#endif
