#ifndef UI_H
#define UI_H

#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include "ChessBoard.h"
using std::cout;

class UI
{
public:
	ChessBoard chessBoard;

    // 印出遊戲畫面
	static void printUI();



	// 取得當前游標位置
	static position getCursorPos();

    // 設定當前輸出底色
    static void SetColor(int = 7);

    // 設定游標位置
    static void SetPosition(position);

    // 讀取鍵盤
    void readKeyBoard();

private:
    // 當前游標位置
    static position cursorPosition;
    Chess* lastChosed;
    
};

bool showAlert(string);
// 跳出選單
int showMenu();

position cursorToChess(position);

#endif // !UI_H

