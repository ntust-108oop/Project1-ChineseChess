#include "UI.h"
#include "Record.h"
// #include "Marquee.h"


using namespace std;

int main()
{
    setWindow(110, 26);

	UI thisGameUI;
	
	thisGameUI.printUI();
	thisGameUI.chessBoard.printThePlane();
	Record::printRecord();
	// Marquee::runWord();

    thisGameUI.readKeyBoard();

}