#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>

struct position
{
    int x, y;
    bool operator==(position other)
    {
        if (x == other.x&&y == other.y)return true;
        else return false;
    }
};

// 設定顏色
void SetColor(int = 0x07);
// 設定游標位置
void SetPosition(position);
// 取得游標位置
position getCursorPosition();
// 取得游標是否顯示
void setCursorVisable(bool);

// 轉換座標
position cursorToChess(position);
position chessToCursor(position);

#endif // !CONSOLE_H
