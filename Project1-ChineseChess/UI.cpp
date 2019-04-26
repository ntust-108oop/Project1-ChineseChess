#include "UI.h"

int UI::color = 7;
position UI::cursorPosition = { 0,0 };

void UI::readKeyBoard()
{
    SetPosition({ 10,10 });
    char input;
    while (1)
    {
        input = _getch();
        switch (input)
        {
        case 0X1B:          // ESC
            return;
        case 0x48:          //上
            cursorPosition.y--;
            SetPosition(cursorPosition);
            break;
        case 0x50:          //下
            cursorPosition.y++;
            SetPosition(cursorPosition);
            break;
        case  0x4B:         //左
            cursorPosition.x--;
            SetPosition(cursorPosition);
            break;
        case  0x4D:         //右
            cursorPosition.x++;
            SetPosition(cursorPosition);
            break;
        }
    }



}

void UI::printUI()
{
    keybd_event(VK_MENU, 0x38, 0, 0);                   // 全螢幕
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_MENU, 0xb8, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_RETURN, 0x9c, KEYEVENTF_KEYUP, 0);

    short TOP_BOUND = 1, BOTTOM_BOUND = 40, LEFT_BOUND = 1, RIGHT_BOUND = 148, ROW_ONE = 39, ROW_TWO = 107;

    for (short i = LEFT_BOUND; i <= RIGHT_BOUND; i++)   // 畫橫線
    {
        SetPosition({ i,TOP_BOUND });
        cout << "/";
        SetPosition({ i,BOTTOM_BOUND });
        cout << "/";
    }
    for (short i = TOP_BOUND; i <= BOTTOM_BOUND; i++)   // 畫直線
    {
        SetPosition({ LEFT_BOUND,i });
        cout << "/";
        SetPosition({ RIGHT_BOUND,i });
        cout << "/";
        SetPosition({ ROW_ONE,i });
        cout << "/";
        SetPosition({ ROW_TWO,i });
        cout << "/";
    }

    // 畫標題
    SetColor(100);
    SetPosition({ ROW_TWO + 11,TOP_BOUND + 8 });
    cout << " ＿＿＿＿＿＿＿＿＿＿ ";
    SetPosition({ ROW_TWO + 11,TOP_BOUND + 9 });
    cout << "｜　　Chinese　　 　｜";
    SetPosition({ ROW_TWO + 11,TOP_BOUND + 10 });
    cout << "｜　　　　Chess　　 ｜";
    SetPosition({ ROW_TWO + 11,TOP_BOUND + 11 });
    cout << " ￣￣￣￣￣￣￣￣￣￣ ";
    SetColor(7);

    // 畫選單
    SetPosition({ ROW_TWO + 13,TOP_BOUND + 23 });
    cout << "方向鍵：移動游標";
    SetPosition({ ROW_TWO + 13,TOP_BOUND + 26 });
    cout << " Enter：選棋/確定";
    SetPosition({ ROW_TWO + 13,TOP_BOUND + 29 });
    cout << "　U　：  悔 棋";
    SetPosition({ ROW_TWO + 13,TOP_BOUND + 32 });
    cout << "　U　：  還 原";
    SetPosition({ ROW_TWO + 13,TOP_BOUND + 35 });
    cout << "ＥＳＣ：離開遊戲";

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