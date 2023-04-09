#include "global.h"
#include "menu.h"
#include "handle.h"
// // ======================================================================================

int main(int argc, char *argv[])
{
    init();
    system("cls");
    
    showMenu();
    freeAll();
    return 0;
}
