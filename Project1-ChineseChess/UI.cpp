#include "UI.h"

int UI::color = 7;
position UI::cursorPosition = { 0,0 };

void UI::readKeyBoard()
{
    char input;
    while (1)
    {
        cin >> input;
        switch (input)
        {
        case 0X1B:          // ESC
            return;
        case 0x48:          //¤W
            cursorPosition.y --;
            break;
        case 0x50:          //¤U
            cursorPosition.y ++;
            break;
        case  0x4B:         //¥ª
            cursorPosition.x --;
            break;
        case  0x4D:         //¥k
            cursorPosition.x ++;
            break;
        }
    }
    
    
    
}

void UI::printUI()
{
}

void UI::showMenu()
{
}


position UI::getCursorPos()
{
    return cursorPosition;
}

void UI::SetColor(int newColor)
{
    UI::color = newColor;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void UI::SetPosition(position newPosition)
{
    UI::cursorPosition = newPosition;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(cursorPosition.x),static_cast<short>(cursorPosition.y) });
}