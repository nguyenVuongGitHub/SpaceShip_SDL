#include "global.h"
#include "menu.h"
#include "handle.h"
#include "player.h"
// // ======================================================================================

int main(int argc, char *argv[])
{
    system("cls");
    init();
    showMenu();

    saveFile(lpr);
    cleanUp();
    freeAll();
    return 0;
}
