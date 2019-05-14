#include "UI.h"
#include "Record.h"

using namespace std;

int main()
{
    setConsole(110, 30, 18);

	UI thisGameUI;
	thisGameUI.printStartScreen("start.txt");
	thisGameUI.printUI();
	thisGameUI.chessBoard.printThePlane();
	Record::printRecord();

    thisGameUI.readKeyBoard();

}