#include "menu.h"

HMENU file, cube_opt, menu;

void InitMenu(HWND hwnd) {
    HMENU menu = CreateMenu();

    file = CreatePopupMenu();
    cube_opt = CreatePopupMenu();


    AppendMenu(menu, MF_STRING | MF_ENABLED | MF_POPUP, file, L"File");
        AppendMenu(file, MF_STRING | MF_ENABLED, LOAD_BTN, L"Import..  (I)");
        AppendMenu(file, MF_STRING | MF_ENABLED, SAVE_BTN, L"Export..  (E)");
        AppendMenu(file, MF_SEPARATOR, 0, NULL);
        AppendMenu(file, MF_STRING | MF_ENABLED, EXIT_BTN, L"Exit         (Esc)");

    AppendMenu(menu, MF_STRING | MF_ENABLED | MF_POPUP, cube_opt, L"Cube");
        AppendMenu(cube_opt, MF_STRING | MF_ENABLED, NEW_BTN, L"New            (N)");
        //AppendMenu(cube_opt, MF_STRING | MF_ENABLED, EXECUTE_BTN, "Execute..   (Enter)");
        AppendMenu(cube_opt, MF_STRING | MF_ENABLED, MIX_BTN, L"Mix            (M)");
        AppendMenu(cube_opt, MF_STRING | MF_ENABLED, SOLVE_BTN, L"Solve          (S)");

    AppendMenu(menu, MF_STRING | MF_ENABLED , ABOUT_BTN, L"About");

    SetMenu(hwnd, menu);
}
