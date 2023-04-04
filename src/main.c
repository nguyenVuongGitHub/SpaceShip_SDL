#include "global.h"
#include "menu.h"
#include "handle.h"
// // ======================================================================================


int main(int argc, char *argv[])
{
    system("cls");
    init();
    showMenu();
    // gameLoop();
    // printf("cc");
    freeAll();
    return 0;
}
