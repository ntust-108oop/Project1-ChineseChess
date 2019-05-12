#include "UI.h"
#include "Record.h"
// #include "Marquee.h"


using namespace std;

int main()
{
    setConsole(110, 26);

	UI thisGameUI;
    Music::setMusic(3);
	thisGameUI.printUI();
	thisGameUI.chessBoard.printThePlane();
	Record::printRecord();
	// Marquee::runWord();

    thisGameUI.readKeyBoard();

}