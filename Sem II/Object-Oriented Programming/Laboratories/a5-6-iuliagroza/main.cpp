#include "ui/UI.h"
#include "tests/Tests.h"

/*
 * Main program
 */
int main() {
    Tests test;
    test.test_all();

    UI ui;
    ui.start();
    return 0;
}
