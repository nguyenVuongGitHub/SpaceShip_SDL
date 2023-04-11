#include "global.h"
#include "menu.h"
#include "handle.h"
// // ======================================================================================

int main(int argc, char *argv[])
{
    system("cls");
    init();
    
    showMenu();
    freeAll();
    return 0;
}
