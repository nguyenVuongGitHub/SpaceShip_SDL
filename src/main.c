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
    printf("\nhello");
    saveFile(lpr);
    freeAll();
    return 0;
}
/*

    menu 2 while lồng
    {

        gameLoop 2 while lồng{
            + handlePause 4 while lồng{
                + menu
                + 
            }
        }

        showHelp 2 while lồng {
            + gameLoop

            + showMenu
        }
        showRank 2 while lồng
    }
*/