#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

class Menu
{
    enum Button
    {
        ENTER = 13,
        ESC = 27,
        UP = 72,
        DOWN = 80
    };
    void positionXY(short x, short y);
    int keystroke();
    void menuDisplay();

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string menu[2]{ "Новая игра", "Выход" };
    int activeMenu = 0;

public:
    void consoleCursorVisible(bool show, short size);

    int menuInteraction();
};