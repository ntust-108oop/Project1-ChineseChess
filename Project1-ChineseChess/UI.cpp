#include "UI.h"

position UI::cursorPosition = { 0,0 };

const short TOP_BOUND = 1, BOTTOM_BOUND = 28, LEFT_BOUND = 1, RIGHT_BOUND = 106, ROW_ONE = 28, ROW_TWO = 66;

// Intent: 讀取鍵盤
// Pre: UI物件
// Post: 依據鍵盤傳入的值做出反應
void UI::readKeyBoard()
{
    const char ESC = 0x1B, UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D;
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
            if (cursorPosition.y + 2 < BOTTOM_BOUND )
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
        case ESC:                                      // 離開遊戲
            if (showAlert("要關閉遊戲嗎？") == true)
            {
                return;
            }
            else
            {
                // 不結束就直接印原本棋盤把alert蓋掉
                chessBoard.printThePlane();
            }
            break;
        case 'u':
        case 'U':                                       // 悔棋
            if (showAlert("　要悔棋嗎？　") == true)
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
            if (showAlert("　要還原嗎？　") == true)
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
    SetPosition({ LEFT_BOUND+2, BOTTOM_BOUND-1 });              // 左欄的下邊
    for (short i = 0; i < ROW_ONE-2; i++)
    {
        cout << "═";
    }
    SetPosition({ ROW_TWO, TOP_BOUND + 1 });             // 右欄的上邊
    for (short i = 0; i < RIGHT_BOUND-2-ROW_TWO; i++)
    {
        cout << "═";
    }
    SetPosition({ ROW_TWO + 1, BOTTOM_BOUND - 1 });          // 右欄的下邊
    for (short i = 0; i < RIGHT_BOUND - 2 - ROW_TWO; i++)
    {
        cout << "═";
    }
    SetPosition({ ROW_TWO, BOTTOM_BOUND -9 });                  // 右欄的分隔線
    for (short i = 0; i < RIGHT_BOUND - ROW_TWO-1; i++)
    {
        cout << "═";
    }

    SetPosition({ LEFT_BOUND, TOP_BOUND });                 // 印角角
    cout << "╔";
    SetPosition({ LEFT_BOUND+2, TOP_BOUND+1 });
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
    SetPosition({ ROW_TWO, BOTTOM_BOUND -1 });
    cout << "╚";

    SetPosition({ RIGHT_BOUND, BOTTOM_BOUND });
    cout << "╝";
    SetPosition({ RIGHT_BOUND - 2, BOTTOM_BOUND - 1 });
    cout << "╝";
    SetPosition({ ROW_ONE, BOTTOM_BOUND - 1 });
    cout << "╝";

    SetPosition({ ROW_TWO, BOTTOM_BOUND - 9 });
    cout << "╠";
    SetPosition({ RIGHT_BOUND-2, BOTTOM_BOUND - 9 });
    cout << "╣";

    SetPosition({ LEFT_BOUND+6, TOP_BOUND + 1 });           // 印字
    cout << "  戰  況  顯  示  ";
    SetPosition({ROW_TWO+6,BOTTOM_BOUND-8});
    cout << "ESC 選單    < 悔棋    > 還原";
    SetPosition({ ROW_TWO + 9,BOTTOM_BOUND - 6 });
    cout << "Enter     選取棋子";
    SetPosition({ ROW_TWO + 11,BOTTOM_BOUND - 4 });
    cout << "↑";
    SetPosition({ ROW_TWO + 9,BOTTOM_BOUND - 3 });
    cout << "←  →  方向鍵控制游標";
    SetPosition({ ROW_TWO + 11,BOTTOM_BOUND - 2 });
    cout << "↓";
}

// Intent: 跳出Y/N視窗
// Pre: UI物件
// Post: 回傳真假值
bool showAlert(string message)
{
    for (short i = LEFT_BOUND + 44; i <= RIGHT_BOUND - 46; i++)     // 畫橫線
    {
        UI::SetPosition({ i,TOP_BOUND + 10 });
        cout << "-";
        for (short j = TOP_BOUND + 11; j <= BOTTOM_BOUND - 11; j++)
        {
            UI::SetPosition({ i,j });
            cout << " ";
        }
        UI::SetPosition({ i,BOTTOM_BOUND - 10 });
        cout << "-";
    }

    for (short i = TOP_BOUND + 10; i <= BOTTOM_BOUND - 10; i++)     // 畫直線
    {

        UI::SetPosition({ ROW_ONE + 5,i });
        cout << "|";
        UI::SetPosition({ ROW_TWO - 5,i });
        cout << "|";
    }

    UI::SetCursorVisible(false);                                    // 印出內容並隱藏游標
    UI::SetPosition({ LEFT_BOUND + 65,TOP_BOUND + 18 });
    cout << message;
    UI::SetPosition({ LEFT_BOUND + 63,TOP_BOUND + 21 });
    cout << "[Y]確定   [N]取消";
    UI::SetPosition({ 200,100 });

    char decision;                                                  // 選擇確定或取消
    while (1)
    {
        decision = _getch();
        switch (decision)
        {
        case 'y':
        case 'Y':
            UI::SetCursorVisible(true);
            UI::SetPosition({ 50,5 });
            return true;
        case 'n':
        case 'N':
            UI::SetCursorVisible(true);
            UI::SetPosition({ 50,5 });
            return false;
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

// Intent: 設定游標是否顯示及大小
// Pre: UI物件
// Post: 游標顯示狀態被改變
void UI::SetCursorVisible(bool visible, DWORD size)
{
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = visible;
    cci.dwSize = size;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}