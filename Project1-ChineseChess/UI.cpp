#include "UI.h"

position UI::cursorPosition = { 0,0 };

const short TOP_BOUND = 1, BOTTOM_BOUND = 40, LEFT_BOUND = 1, RIGHT_BOUND = 148, ROW_ONE = 39, ROW_TWO = 107;

// Intent: 讀取鍵盤
// Pre: UI物件
// Post: 依據鍵盤傳入的值做出反應
void UI::readKeyBoard()
{
    const char ESC = 0x1B, UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D;
    SetPosition({ ROW_ONE + 11,TOP_BOUND + 4 });
    char input;
    while (1)
    {
        input = _getch();
        switch (input)
        {
        case UP:                                        //上
            if (cursorPosition.y - 4 > TOP_BOUND + 2)
            {
                cursorPosition.y -= 4;
                SetPosition(cursorPosition);
            }
            break;
        case DOWN:                                      // 下
            if (cursorPosition.y + 4 < BOTTOM_BOUND - 2)
            {
                cursorPosition.y += 4;
                SetPosition(cursorPosition);
            }
            break;
        case  LEFT:                                     // 左
            if (cursorPosition.x - 5 > ROW_ONE + 10)
            {
                cursorPosition.x -= 5;
                SetPosition(cursorPosition);
            }
            break;
        case  RIGHT:                                     // 右
            if (cursorPosition.x + 5 < ROW_TWO - 10)
            {
                cursorPosition.x += 5;
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
    keybd_event(VK_MENU, 0x38, 0, 0);                   // 設定全螢幕
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
    
    SetColor(100);                                      // 畫標題
    SetPosition({ ROW_TWO + 11,TOP_BOUND + 4 });
    cout << " ＿＿＿＿＿＿＿＿＿＿ ";
    SetPosition({ ROW_TWO + 11,TOP_BOUND + 5 });
    cout << "｜　　Chinese　　 　｜";
    SetPosition({ ROW_TWO + 11,TOP_BOUND + 6 });
    cout << "｜　　　　Chess　　 ｜";
    SetPosition({ ROW_TWO + 11,TOP_BOUND + 7 });
    cout << " ￣￣￣￣￣￣￣￣￣￣ ";
    SetColor(7);

    SetPosition({ ROW_TWO + 13,TOP_BOUND + 15 });       // 顯示輪到誰
    cout << "目前輪到";
    //if (chessBoard.getTurn() == 0)        // static function 無法使用 非static 的chessBoard
    //                                      // 這段可能給ChessBoard 來印比較好
    //{
    //    SetColor(240);
    //    cout << "黑方";
    //}
    //else
    //{
    SetColor(252);
    cout << "紅方";
    //}
    SetColor(7);
    cout << "下棋";

    SetPosition({ ROW_TWO + 13,TOP_BOUND + 24 });       // 畫選單
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