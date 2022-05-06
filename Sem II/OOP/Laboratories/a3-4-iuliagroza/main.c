#include "repository/OfferRepo.h"
#include "controller/Controller.h"
#include "ui/Ui.h"
#include "tests/Tests.h"

/*
 * Main function
 * */
int main() {
    testAll();

    OfferRepo *repo = createRepo();
    OperationStack *undoStack = createOperationStack();
    OperationStack *redoStack = createOperationStack();

    Controller *ctrl = createController(repo, undoStack, redoStack);

    UI *ui = createUI(ctrl);

    run(ui);

    destroyUI(ui);
    return 0;
}

