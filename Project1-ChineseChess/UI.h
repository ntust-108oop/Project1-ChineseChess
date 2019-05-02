#ifndef UI_H
#define UI_H

#include <windows.h>
#include <conio.h>
#include <iostream>
#include "ChessBoard.h"
using namespace std;

class UI
{
public:
	ChessBoard chessBoard;

    // 印出遊戲畫面
	static void printUI();

    static void showMenu();

	// 取得當前游標位置
	static position getCursorPos();

    // 設定當前輸出底色
    static void SetColor(int = 7);

    // 設定游標位置
    static void SetPosition(position);

    // 設定是否顯示游標
    static void SetCursorVisible(bool, DWORD=1);

    // 讀取鍵盤
    void readKeyBoard();

private:
    // 當前游標位置
    static position cursorPosition;
    
};

bool showAlert(string);

#endif // !UI_H

