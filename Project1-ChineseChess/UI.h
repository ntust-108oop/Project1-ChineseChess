#ifndef UI_H
#define UI_H
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <direct.h>
#include "ChessBoard.h"
#include "Record.h"
#include <thread>
#include "Music.h"
using std::cout;

class UI
{
public:
    UI();

    // 印出遊戲畫面
    static void printUI();

    // 讀取鍵盤
    void readKeyBoard();

    // 跳出確認視窗
    bool showAlert(string, bool);
    bool showAlert(string, bool, string);

    // 跳出輸入視窗
    string showInput(string);

    // 跳出獲勝視窗
    bool showWin(unsigned);

    // 跳出選單
    int showMenu();

    ChessBoard chessBoard;

private:
    Chess* lastChosed;
    bool cueMode;
};

#endif // !UI_H

