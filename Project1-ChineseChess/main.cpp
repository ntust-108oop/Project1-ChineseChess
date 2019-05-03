#include "UI.h"
#include "Record.h"

using namespace std;

int main()
{
	UI thisGameUI;
	// thisGameUI.chessBoard.readTheBoard("file.txt");

	thisGameUI.printUI();
	thisGameUI.chessBoard.printThePlane();
	Record::printRecord();

    thisGameUI.readKeyBoard();

}