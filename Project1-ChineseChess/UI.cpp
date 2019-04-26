#include "UI.h"

int UI::color = 7;
position UI::cursorPosition = { 0,0 };

static short TOP_BOUND = 1, BOTTOM_BOUND = 40, LEFT_BOUND = 1, RIGHT_BOUND = 148, ROW_ONE = 39, ROW_TWO = 107;

void UI::readKeyBoard()
{
    SetPosition({ ROW_ONE + 11,TOP_BOUND + 4 });
    char input;
    while (1)
    {
        input = _getch();
        switch (input)
        {
        case 0X1B:          // ESC
            return;
        case 0x48:          //上
            if (cursorPosition.y - 4 > TOP_BOUND + 2)
            {
                cursorPosition.y -= 4;
                SetPosition(cursorPosition);
            }
            break;
        case 0x50:          //下
            if (cursorPosition.y + 4 < BOTTOM_BOUND - 2)
            {
                cursorPosition.y += 4;
                SetPosition(cursorPosition);
            }
            break;
        case  0x4B:         //左
            if (cursorPosition.x - 5 > ROW_ONE + 10)
            {
                cursorPosition.x -= 5;
                SetPosition(cursorPosition);
            }
            break;
        case  0x4D:         //右
            if (cursorPosition.x + 5 < ROW_TWO - 10)
            {
                cursorPosition.x += 5;
                SetPosition(cursorPosition);
            }
            break;
        case 'u':
        case 'U':
            // 悔棋
            // showAlert("要悔棋嗎？");
            break;
        case 'r':
        case 'R':
            // 還原
            // showAlert("要還原嗎？");
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
    SetPosition({ ROW_TWO + 11,TOP_BOUND + 4 });
    cout << " ＿＿＿＿＿＿＿＿＿＿ ";
    SetPosition({ ROW_TWO + 11,TOP_BOUND + 5 });
    cout << "｜　　Chinese　　 　｜";
    SetPosition({ ROW_TWO + 11,TOP_BOUND + 6 });
    cout << "｜　　　　Chess　　 ｜";
    SetPosition({ ROW_TWO + 11,TOP_BOUND + 7 });
    cout << " ￣￣￣￣￣￣￣￣￣￣ ";
    SetColor(7);

    // 指示
    SetPosition({ ROW_TWO + 13,TOP_BOUND + 15 });
    cout << "目前輪到";
    SetColor(252);
    cout << "紅方";
    SetColor(7);
    cout << "下棋";
    SetPosition({ ROW_TWO + 13,TOP_BOUND + 16 });
    cout << "不然就是";
    SetColor(240);
    cout << "黑方";
    SetColor(7);
    cout << "下棋";


    // 畫選單
    SetPosition({ ROW_TWO + 13,TOP_BOUND + 24 });
    cout << "方向鍵：移動游標";
    SetPosition({ ROW_TWO + 13,TOP_BOUND + 27 });
    cout << " Enter：選棋/確定";
    SetPosition({ ROW_TWO + 13,TOP_BOUND + 30 });
    cout << "　Ｕ　：  悔 棋";
    SetPosition({ ROW_TWO + 13,TOP_BOUND + 33 });
    cout << "　Ｒ　：  還 原";
    SetPosition({ ROW_TWO + 13,TOP_BOUND + 36 });
    cout << "ＥＳＣ：離開遊戲";

    
}

void UI::showMenu()
{

}

void showAlert(string message)
{
    for (short i = LEFT_BOUND + 44; i <= RIGHT_BOUND - 46; i++)   // 畫橫線
    {
        UI::SetPosition({ i,TOP_BOUND + 10 });
        cout << "-";
        for (short j = TOP_BOUND+11; j <= BOTTOM_BOUND-11; j++)
        {
            UI::SetPosition({ i,j });
            cout << " ";
        }
        UI::SetPosition({ i,BOTTOM_BOUND - 10 });
        cout << "-";
    }
    for (short i = TOP_BOUND + 10; i <= BOTTOM_BOUND - 10; i++)   // 畫直線
    {

        UI::SetPosition({ ROW_ONE + 5,i });
        cout << "|";
        UI::SetPosition({ ROW_TWO - 5,i });
        cout << "|";
    }
    UI::SetPosition({ LEFT_BOUND + 70,TOP_BOUND + 20 });
    cout << message;
    
    // 只寫到跳出視窗 沒寫關閉視窗
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