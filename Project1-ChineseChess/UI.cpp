#include "UI.h"

position UI::cursorPosition = { 0,0 };

const short TOP_BOUND = 1, BOTTOM_BOUND = 28, LEFT_BOUND = 1, RIGHT_BOUND = 106, ROW_ONE = 28, ROW_TWO = 66;
const char ESC = 0x1B, UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D, ENTER = 0x0D;

// Intent: 讀取鍵盤
// Pre: UI物件
// Post: 依據鍵盤傳入的值做出反應
void UI::readKeyBoard()
{

    SetPosition({ ROW_ONE + 3,TOP_BOUND + 3 });
    char input;
    while (1)
    {
        input = _getch();
        switch (input)
        {
        case UP:                                        //上
            if (cursorPosition.y - 2 > TOP_BOUND + 2)
            {
                cursorPosition.y -= 2;
                SetPosition(cursorPosition);
            }
            break;
        case DOWN:                                      // 下
            if (cursorPosition.y + 2 < BOTTOM_BOUND)
            {
                cursorPosition.y += 2;
                SetPosition(cursorPosition);
            }
            break;
        case  LEFT:                                     // 左
            if (cursorPosition.x - 4 > ROW_ONE + 2)
            {
                cursorPosition.x -= 4;
                SetPosition(cursorPosition);
            }
            break;
        case  RIGHT:                                     // 右
            if (cursorPosition.x + 4 < ROW_TWO - 2)
            {
                cursorPosition.x += 4;
                SetPosition(cursorPosition);
            }
            break;
        case ESC:                                      // 選單
            switch (showMenu())
            {
            case 0:                                     // 繼續遊戲
                chessBoard.printThePlane();
                break;
            case 1:                                     // 重新開始
                // 再看看需不需要做
                chessBoard.printThePlane();
                break;
            case 2:                                     // 回主選單(?
                // 再看看需不需要做
                chessBoard.printThePlane();
                break;
            case 3:                                     // 結束遊戲
                if (showAlert("結束遊戲？") == true)
                {
                    return;
                }
                else
                {
                    chessBoard.printThePlane();
                }
                break;
            }
            break;
        case 'u':
        case 'U':                                       // 悔棋
            if (showAlert("確定悔棋？") == true)
            {
                /*

                這裡要 call 悔棋的function

                */
                // ↓悔棋後印出更新後的棋盤
                chessBoard.printThePlane();
            }
            else
            {
                // 不悔棋就直接印原本棋盤把alert蓋掉
                chessBoard.printThePlane();
            }
            break;
        case 'r':
        case 'R':                                       // 還原
            if (showAlert("確定還原？") == true)
            {
                /*

                這裡要 call 還原的function

                */
                // ↓還原後印出更新後的棋盤
                chessBoard.printThePlane();
            }
            else
            {
                // 不還原就直接印原本棋盤把alert蓋掉
                chessBoard.printThePlane();
            }
            break;
        }
    }
}

// Intent: 印出操作畫面
// Pre: UI物件
// Post: 印出結果
void UI::printUI()
{

    for (short i = 0; i < BOTTOM_BOUND - 1; i++)            // 印直線
    {
        SetPosition({ LEFT_BOUND, TOP_BOUND + i });             // 最左兩條
        cout << "║ ║";
        SetPosition({ ROW_ONE, TOP_BOUND + i });                // 棋盤左邊
        cout << "║";
        SetPosition({ ROW_TWO, TOP_BOUND + i });                // 棋盤右邊
        cout << "║";
        SetPosition({ RIGHT_BOUND - 2, TOP_BOUND + i });        // 最右兩條
        cout << "║ ║";
    }

    SetPosition({ LEFT_BOUND, TOP_BOUND });                 // 印橫線
    for (short i = 0; i < RIGHT_BOUND - 1; i++)                 // 最上
    {
        cout << "═";
    }
    SetPosition({ LEFT_BOUND, BOTTOM_BOUND });                  // 最下
    for (short i = 0; i < RIGHT_BOUND - 1; i++)
    {
        cout << "═";
    }
    SetPosition({ LEFT_BOUND + 2, TOP_BOUND + 1 });             // 左欄的上邊
    for (short i = 0; i < ROW_ONE - 2; i++)
    {
        cout << "═";
    }
    SetPosition({ LEFT_BOUND + 2, BOTTOM_BOUND - 1 });              // 左欄的下邊
    for (short i = 0; i < ROW_ONE - 2; i++)
    {
        cout << "═";
    }
    SetPosition({ ROW_TWO, TOP_BOUND + 1 });             // 右欄的上邊
    for (short i = 0; i < RIGHT_BOUND - 2 - ROW_TWO; i++)
    {
        cout << "═";
    }
    SetPosition({ ROW_TWO + 1, BOTTOM_BOUND - 1 });          // 右欄的下邊
    for (short i = 0; i < RIGHT_BOUND - 2 - ROW_TWO; i++)
    {
        cout << "═";
    }
    SetPosition({ ROW_TWO, BOTTOM_BOUND - 9 });                  // 右欄的分隔線
    for (short i = 0; i < RIGHT_BOUND - ROW_TWO - 1; i++)
    {
        cout << "═";
    }

    SetPosition({ LEFT_BOUND, TOP_BOUND });                 // 印角角
    cout << "╔";
    SetPosition({ LEFT_BOUND + 2, TOP_BOUND + 1 });
    cout << "╔";
    SetPosition({ ROW_TWO, TOP_BOUND + 1 });
    cout << "╔";

    SetPosition({ RIGHT_BOUND, TOP_BOUND });
    cout << "╗";
    SetPosition({ RIGHT_BOUND - 2, TOP_BOUND + 1 });
    cout << "╗";
    SetPosition({ ROW_ONE, TOP_BOUND + 1 });
    cout << "╗";

    SetPosition({ LEFT_BOUND, BOTTOM_BOUND });
    cout << "╚";
    SetPosition({ LEFT_BOUND + 2, BOTTOM_BOUND - 1 });
    cout << "╚";
    SetPosition({ ROW_TWO, BOTTOM_BOUND - 1 });
    cout << "╚";

    SetPosition({ RIGHT_BOUND, BOTTOM_BOUND });
    cout << "╝";
    SetPosition({ RIGHT_BOUND - 2, BOTTOM_BOUND - 1 });
    cout << "╝";
    SetPosition({ ROW_ONE, BOTTOM_BOUND - 1 });
    cout << "╝";

    SetPosition({ ROW_TWO, BOTTOM_BOUND - 9 });
    cout << "╠";
    SetPosition({ RIGHT_BOUND - 2, BOTTOM_BOUND - 9 });
    cout << "╣";

    SetPosition({ LEFT_BOUND + 6, TOP_BOUND + 1 });           // 印字
    cout << "  戰  況  顯  示  ";
    SetPosition({ ROW_TWO + 6,BOTTOM_BOUND - 8 });
    cout << "ESC 選單    U 悔棋    R 還原";
    SetPosition({ ROW_TWO + 9,BOTTOM_BOUND - 6 });
    cout << "Enter     選取棋子";
    SetPosition({ ROW_TWO + 11,BOTTOM_BOUND - 4 });
    cout << "↑";
    SetPosition({ ROW_TWO + 9,BOTTOM_BOUND - 3 });
    cout << "←  →  方向鍵控制游標";
    SetPosition({ ROW_TWO + 11,BOTTOM_BOUND - 2 });
    cout << "↓";
}

// Intent: 跳出選單
// Pre: UI物件
// Post: 回傳選擇
int showMenu()
{
    vector<string> list = { "繼續遊戲", "重新開始", "回主選單", "結束遊戲" };
    const short MENU_TOP = 10, MENU_LEFT = 38, MENU_RIGHT = 57;
    short menuBottem = MENU_TOP + list.size() * 2;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x01);      // 設定黑底藍字

    for (short i = MENU_TOP; i < menuBottem; i++)              // 印黑底
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MENU_LEFT,i });
        for (short j = MENU_LEFT; j <= MENU_RIGHT; j++)
        {
            cout << " ";
        }
    }
    for (short i = MENU_LEFT; i <= MENU_RIGHT; i++)     // 畫橫線
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { i,MENU_TOP });
        cout << "═";
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { i,menuBottem });
        cout << "═";
    }

    for (short i = MENU_TOP; i < menuBottem; i++)     // 畫直線
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MENU_LEFT,i });
        cout << "║";
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MENU_RIGHT - 1,i });
        cout << "║";
    }

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MENU_LEFT,menuBottem });
    cout << "╙";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MENU_RIGHT - 1,menuBottem });
    cout << "╜";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MENU_LEFT,MENU_TOP });
    cout << "╓";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MENU_RIGHT - 1,MENU_TOP });
    cout << "╖";


    CONSOLE_CURSOR_INFO temp;                                                   // 隱藏游標
    temp.dwSize = 100;
    temp.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &temp);

    char key, choice = 0;
    for (short i = 0; i < static_cast<short>(list.size()); i++)
    {
        if (i == choice)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x70);      // 設定白底黑字
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);      // 設定黑底白字
        }
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MENU_LEFT + 6,MENU_TOP + 1 + 2 * i });
        cout << list[i];
    }
    while (1)
    {
        key = _getch();
        switch (key)
        {
        case UP:
            if (choice > 0)
            {
                choice--;
            }
            else
            {
                choice = 3;
            }
            for (short i = 0; i < static_cast<short>(list.size()); i++)
            {
                if (i == choice)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x70);      // 設定白底黑字
                }
                else
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);      // 設定黑底白字
                }
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MENU_LEFT + 6,MENU_TOP + 1 + 2 * i });
                cout << list[i];
            }
            break;
        case DOWN:
            if (choice < 3)
            {
                choice++;
            }
            else
            {
                choice = 0;
            }
            for (short i = 0; i < static_cast<short>(list.size()); i++)
            {
                if (i == choice)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x70);      // 設定白底黑字
                }
                else
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);      // 設定黑底白字
                }
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MENU_LEFT + 6,MENU_TOP + 1 + 2 * i });
                cout << list[i];
            }
            break;
        case ENTER:
            temp.dwSize = 100;
            temp.bVisible = true;
            SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &temp);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { ROW_ONE + 3,TOP_BOUND + 3 });

            return choice;
            break;
        }
    }
}

// Intent: 跳出Y/N視窗
// Pre: UI物件
// Post: 回傳真假值
bool showAlert(string message)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);      // 設定黑底白字

    for (short i = TOP_BOUND + 10; i < BOTTOM_BOUND - 9; i++)              // 印黑底
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 8),static_cast<short>(i) });
        for (unsigned j = ROW_ONE + 8; j < ROW_TWO - 6; j++)
        {
            cout << " ";
        }
    }
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 8),static_cast<short>(TOP_BOUND + 10) });
    for (short i = ROW_ONE + 8; i < ROW_TWO - 6; i++)     // 畫橫線
    {
        cout << "═";
    }
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 8),static_cast<short>(BOTTOM_BOUND - 9) });
    for (short i = ROW_ONE + 8; i < ROW_TWO - 6; i++)     // 畫橫線
    {
        cout << "═";
    }
    for (short i = TOP_BOUND + 10; i <= BOTTOM_BOUND - 9; i++)     // 畫直線
    {

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 8),static_cast<short>(i) });
        cout << "║";
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_TWO - 8),static_cast<short>(i) });
        cout << "║";
    }

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 8),static_cast<short>(BOTTOM_BOUND - 9) });
    cout << "╙";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_TWO - 8),static_cast<short>(BOTTOM_BOUND - 9) });
    cout << "╜";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 8),static_cast<short>(TOP_BOUND + 10) });
    cout << "╓";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_TWO - 8),static_cast<short>(TOP_BOUND + 10) });
    cout << "╖";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 16),static_cast<short>(TOP_BOUND + 13) });
    cout << message;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 14),static_cast<short>(TOP_BOUND + 15) });
    cout << "是        否";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 24),static_cast<short>(TOP_BOUND + 15) });

    char key;
    bool choice = false;
    while (1)
    {
        key = _getch();
        switch (key)
        {
        case LEFT:
        case RIGHT:
            if (choice == true)
            {
                choice = false;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 24),static_cast<short>(TOP_BOUND + 15) });
            }
            else
            {
                choice = true;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 14),static_cast<short>(TOP_BOUND + 15) });
            }
            break;
        case ENTER:
            return choice;
        }
    }
}

// Intent: 取得當前游標位置
// Pre: UI物件
// Post: 回傳position
position UI::getCursorPos()
{
    return cursorPosition;
}

// Intent: 設定文字顏色
// Pre: UI物件
// Post: 文字顏色被改變
void UI::SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Intent: 設定游標位置
// Pre: UI物件
// Post: 游標位置被改變
void UI::SetPosition(position newPosition)
{
    UI::cursorPosition = newPosition;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(cursorPosition.x),static_cast<short>(cursorPosition.y) });
}