#include "game.h"
#include "handle.h"
// // ======================================================================================


int main(int argc, char *argv[])
{
    system("cls");
    init();

    gameLoop();
    // printf("cc");
    freeAll();
    return 0;
}
