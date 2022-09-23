#include "Menu.h"

void Menu::positionXY(short x, short y)
{
    SetConsoleCursorPosition(hStdOut, { x, y });
}

void Menu::consoleCursorVisible(bool show, short size)
{
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show;
    structCursorInfo.dwSize = size;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void Menu::menuDisplay()
{
    consoleCursorVisible(false, 10);
    int x = 50;
    int y = 12;

    for (int i = 0; i < size(menu); i++)
    {
        if (i == activeMenu)
            SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        else
            SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);

        positionXY(x, ++y);
        std::cout << menu[i] << std::endl;
    }
}

int Menu::keystroke()
{
    char ch;
    ch = _getch();

    switch (ch)
    {
    case ENTER:
        switch (activeMenu)
        {
        case 0:
            system("color 7");
            system("CLS");
            return ENTER;
        case 1:
            exit(0);
        }
        break;

    case UP:
        if (activeMenu > 0)
            return --activeMenu;
        break;

    case DOWN:
        if (activeMenu < size(menu) - 1)
            return ++activeMenu;
        break;

    case ESC:
        exit(0);
    }
}

int Menu::menuInteraction()
{
    do {
        menuDisplay();
        if (ENTER == keystroke())
        {
            system("CLS");
            return ENTER;
        }
    } while (ENTER);
}