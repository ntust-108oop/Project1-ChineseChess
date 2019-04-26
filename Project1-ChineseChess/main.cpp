#include <iostream>
#include "Chess.h"
#include "ChessBoard.h"
#include "Record.h"
#include "UI.h"

using namespace std;

int main()
{
	UI thisGameUI;
	thisGameUI.chessBoard.readTheBoard("file.txt");

	thisGameUI.printUI();
	thisGameUI.chessBoard.printThePlane();
	Record::printRecord();

	// UIÅª¨úÁä½Lfunction

}