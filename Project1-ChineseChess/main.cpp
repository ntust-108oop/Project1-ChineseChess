#include "UI.h"
#include "Record.h"

using namespace std;

int main()
{
    // setWindow(); //調整視窗大小 字體大小等  修改中

	UI thisGameUI;
    Music::setMusic(2);
	thisGameUI.printUI();
	thisGameUI.chessBoard.printThePlane();
	Record::printRecord();

    thisGameUI.readKeyBoard();

}