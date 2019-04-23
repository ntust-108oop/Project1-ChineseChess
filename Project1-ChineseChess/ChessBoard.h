#pragma once
#include <iostream>
#include <string>
#include "Chess.h"

using namespace std;

class ChessBoard
{
private:
	// 整個棋盤的現在的位置上的內容
	Chess wholePosition[9][10];
	// Black:0 Red:1
	int turns;
	// 當前游標的位置
	int cursorPosition[2];

public:
	ChessBoard();
	~ChessBoard();
	ChessBoard(string fileTxt);

	// UI應該會用到的，取得棋盤內容
	Chess* getTheBoard();

	// 應該在讀入棋盤時創建好所有chess物件
	void readTheBoard(string fileTxt);
	void saveTheBoard();
};

