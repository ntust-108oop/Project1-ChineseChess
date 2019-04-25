#include "UI.h"

int UI::color = 7;
cursorPos UI::cursorPosition = { 0,0 };

UI::UI()
{
}


UI::~UI()
{
}


cursorPos UI::getCursorPos()
{
    return cursorPosition;
}

void UI::SetColor(int newColor)
{
    UI::color = newColor;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void UI::SetPosition(cursorPos newPosition)
{
    UI::cursorPosition = newPosition;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { cursorPosition.x,cursorPosition.y });
}