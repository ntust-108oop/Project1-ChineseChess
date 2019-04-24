#pragma once
#include <iostream>
#include <string>
#include "Chess.h"

using namespace std;

class ChessBoard
{
private:
	// 整個棋盤的現在的位置上的內容
	// 用指標存取，NULL就是當前位置沒有棋子的狀態
	Chess* wholePosition[9][10];
	// Black:0 Red:1
	int turns;


public:
	ChessBoard();
	~ChessBoard();
	ChessBoard(string fileTxt);

	void printThePlane();

	// 應該在讀入棋盤時創建好所有chess物件
	void readTheBoard(string fileTxt);
	void saveTheBoard();
};

