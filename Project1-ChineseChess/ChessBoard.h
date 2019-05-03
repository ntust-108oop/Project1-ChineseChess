#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include "Chess.h"
using namespace std;


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
	// 印出含有選中棋的可動步數的棋盤，使用前需要先確定legalMove內是否已排除拐馬步
	// 或其他特殊規則，以及不能吃得棋，以及被其他棋檔到的剩餘位置
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
	void SetColor(int = 7);//搬UI的函數過來設定顏色
};

void printEmptyPlane();

#endif // !CHESSBOARD_H