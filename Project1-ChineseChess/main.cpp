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

	/*建議不要用while(1)來render，而是while(1)來detect有無輸入才render*/
	while (1)
	{
        


		thisGameUI.printUI(); // 印出整個畫面框架
		Record::printRecord();	// 印出紀錄部分
		//chessBoard.printThePlane();// 印出棋盤
		chessBoard.printThePlaneInCout();// 印出棋盤

		// UI讀取鍵盤

		system("pause");
		system("CLS");	// 清除整個頁面
	}
}