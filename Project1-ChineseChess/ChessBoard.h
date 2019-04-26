#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <iostream>
#include <fstream>
#include <string>
#include "Chess.h"

using namespace std;

class ChessBoard
{
private:
    // 整個棋盤的現在的位置上的內容
    // 用指標存取，NULL就是當前位置沒有棋子的狀態
    Chess* wholePosition[9][10];//[col][row]
    // Black:0 Red:1
    int turns;


public:
    ChessBoard();
    ~ChessBoard();
    ChessBoard(string fileTxt);

    void printThePlane();
	void printThePlaneInCout();

    // 應該在讀入棋盤時創建好所有chess物件
    void readTheBoard(string fileTxt);
    void saveTheBoard(string fileTxt);
	void saveTheBoard();
};



#endif // !CHESSBOARD_H