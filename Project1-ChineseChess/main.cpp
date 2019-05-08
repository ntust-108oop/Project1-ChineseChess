#include "UI.h"
#include "Record.h"

using namespace std;

int main()
{
	UI thisGameUI;

	thisGameUI.printUI();
	thisGameUI.chessBoard.printThePlane();
	Record::printRecord();

    thisGameUI.readKeyBoard();

}