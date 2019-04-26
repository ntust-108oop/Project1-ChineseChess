#ifndef UI_H
#define UI_H

#include <windows.h>
#include <conio.h>
#include <iostream>
#include "ChessBoard.h"
#include "Record.h"
using namespace std;

class UI
{
public:

	ChessBoard chessBoard;

	static void printUI();
	static void showMenu();

	// 取得當前游標位置
	static position getCursorPos();

    // 設定當前輸出底色
    static void SetColor(int = 7);
    // 設定游標位置
    static void SetPosition(position);

    static void readKeyBoard();

private:
    // 當前輸出底色
    static int color;
    // 當前游標位置
    static position cursorPosition;
};

#endif // !UI_H

