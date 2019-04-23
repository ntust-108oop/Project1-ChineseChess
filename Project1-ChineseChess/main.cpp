#include <iostream>
#include "Chess.h"
#include "ChessBoard.h"
#include "Record.h"
#include "UI.h"

using namespace std;

int main()
{
	ChessBoard chessBoard;
	UI nowUI;
	chessBoard.readTheBoard("file.txt");
	while (1)
	{
		nowUI.printUI();

	}
}