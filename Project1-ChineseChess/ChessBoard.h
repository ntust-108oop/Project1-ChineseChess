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

	// 印出普通棋盤
    void printThePlane();
	// 印出含有選中棋的可動步數的棋盤
	void printChosenPlane();


	// 移動棋盤，偵測到選棋時會呼叫
	void moveTheChess(int fromX, int fromY, int toX, int toY);

    // 應該在讀入棋盤時創建好所有chess物件
    void readTheBoard(string fileTxt);
    void saveTheBoard(string fileTxt);
	void saveTheBoard();

	vector <position> legalMove;	//存放能走的路，UI能直接使用到它
	void manageLegalMove(int x, int y);		// UI在選擇棋子以後呼叫的
	void clearLegalMove();
};



#endif // !CHESSBOARD_H