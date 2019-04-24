#include <iostream>
#include "Chess.h"
#include "ChessBoard.h"
#include "Record.h"
#include "UI.h"

using namespace std;

int main()
{
	ChessBoard chessBoard;
	UI thisGameUI;

	chessBoard.readTheBoard("file.txt");
	while (1)
	{
		thisGameUI.printUI(); // 印出整個畫面框架
		Record::printRecord();	// 印出紀錄部分
		chessBoard.printThePlane();		// 印出棋盤
		system("CLS");	// 清除整個頁面
	}
}