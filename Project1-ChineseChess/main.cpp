#include "UI.h"
#include "Record.h"

using namespace std;

int main()
{
    setConsole(110, 26);

	UI thisGameUI;
    Music::setMusic(3);
	thisGameUI.printStartScreen("start.txt");
	thisGameUI.printUI();
	thisGameUI.chessBoard.printThePlane();
	Record::printRecord();

    thisGameUI.readKeyBoard();

}