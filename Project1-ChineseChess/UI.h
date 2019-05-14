#ifndef UI_H
#define UI_H
#include <iostream>
#include <fstream>
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
    void printUI();

    // 讀取鍵盤
    void readKeyBoard();

	// 印起始畫面
	void printStartScreen(string);

    ChessBoard chessBoard;

private:
    
    // 印出setting
    void printSetting();

    // 跳出確定視窗
    void showAlert(vector<string>);

    // 跳出Y/N視窗
    bool showAlert(vector<string>, bool);

    // 跳出輸入視窗
    string showInput(string);

    // 跳出獲勝視窗
    bool showWin(unsigned);

    // 跳出選單
    int showMenu(vector<string>);

	//計算起始畫面圓圈內部的位置
	pair<int, int> compIn(string);

    Chess* lastChosed;
    bool cueMode;
    unsigned music;
};

#endif // !UI_H

