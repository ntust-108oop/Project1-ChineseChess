#include "Console.h"

const short TOP_BOUND = 2, BOTTOM_BOUND = TOP_BOUND + 23, LEFT_BOUND = 1, RIGHT_BOUND = 106, ROW_ONE = LEFT_BOUND + 27, ROW_TWO = ROW_ONE + 38;

// Intent: 設定顏色
// Pre: 顏色編號（0x底字；0黑 3綠 4暗紅 7亮灰 8暗灰 C亮紅 D粉紅 F白 ex. 0x07黑底亮灰字）
// Post: 游標位置被改變
void SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Intent: 設定游標位置
// Pre: 無
// Post: 游標位置被改變
void SetPosition(position newPosition)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(newPosition.x),static_cast<short>(newPosition.y) });
}

// Intent: 取得當前游標位置
// Pre: 無
// Post: 回傳position
position getCursorPosition()
{
    CONSOLE_SCREEN_BUFFER_INFO cSBInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cSBInfo);
    return { cSBInfo.dwCursorPosition.X,cSBInfo.dwCursorPosition.Y };
}

// Intent: 設定游標是否顯示
// Pre: 真假值
// Post: 游標顯示或隱藏
void setCursorVisable(bool set)
{
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 100;
    cci.bVisible = set;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

// Intent: 將游標座標轉為棋盤座標
// Pre: 游標座標
// Post: 棋盤座標
position cursorToChess(position cursorPosition)
{
    position chessPosition;
    chessPosition.x = (cursorPosition.x - ROW_ONE - 3) / 4;
    chessPosition.y = (cursorPosition.y - TOP_BOUND - 3) / 2;
    return chessPosition;
}

// Intent: 將棋盤座標轉為游標座標
// Pre: 棋盤座標
// Post: 游標座標
position chessToCursor(position chessPosition)
{
    position cursorPosition;
    cursorPosition.x = chessPosition.x * 4 + ROW_ONE + 3;
    cursorPosition.y = chessPosition.y * 2 + TOP_BOUND + 3;
    return cursorPosition;
}

void setConsole(int width, int height, int fontSize)
{
    if (width != 1 && height != 1)
    {
        _COORD c;
        c.X = 1;
        c.Y = 1;
        SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }
    _COORD c;
    c.X = width;
    c.Y = height;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), c);

    _SMALL_RECT sr;
    sr.Top = 0;
    sr.Left = 0;
    sr.Right = width-1;
    sr.Bottom = height-1;
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &sr);

    PCONSOLE_FONT_INFOEX pfi = new CONSOLE_FONT_INFOEX();
    pfi->cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, pfi);
    pfi->dwFontSize.X = 0;
    pfi->dwFontSize.Y = fontSize;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, pfi);

    SetConsoleTitle("Chinese Chess");
    
}