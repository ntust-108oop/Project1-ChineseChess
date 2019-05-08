#include "UI.h"
#include "Record.h"

using namespace std;

int main()
{
	UI thisGameUI;
    Music::setMusic(2);
	thisGameUI.printUI();
	thisGameUI.chessBoard.printThePlane();
	Record::printRecord();

    thisGameUI.readKeyBoard();

}