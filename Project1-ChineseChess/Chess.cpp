#include "Chess.h"

Chess::Chess()
{
	chessType = NULL;
	currentPosition.x = NULL;
	currentPosition.y = NULL;
	chosen = NULL;
}

Chess::Chess(int chessTypeInput, int xInput, int yInput)
{
	chessType = chessTypeInput;
	currentPosition.x = xInput;
	currentPosition.y = yInput;
	chosen = false;
}

Chess::~Chess()
{

}

int Chess::getChessType()
{
	return chessType;
}

void Chess::setCurrentPosition(int xInput, int yInput)
{
	currentPosition.x = xInput;
	currentPosition.y = yInput;
}

position Chess::getCurrentPosition()
{
	return currentPosition;
}

void Chess::setChosen(bool chosenInput)
{
	chosen = chosenInput;
}

bool Chess::getChosen()
{
	return chosen;
}

void Chess::setLegalMove()
{
	position temp = currentPosition;
	switch (chessType)
	{
	case 1: //黑將
		if (temp.x > 3) //向左
		{
			temp.x--;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.x < 5) //向右
		{
			temp.x++;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.y > 0) //向上
		{
			temp.y--;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.y < 2) //向下
		{
			temp.y++;
			legalMove.push_back(temp);
		}
		break;

	case 2: //黑士
		if (temp.x > 3 && temp.y > 0) //向左上
		{
			temp.x--;
			temp.y--;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.x < 5 && temp.y > 0) //向右上
		{
			temp.x++;
			temp.y--;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.x > 3 && temp.y < 2) //向左下
		{
			temp.x--;
			temp.y++;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.x < 5 && temp.y < 2) //向右下
		{
			temp.x++;
			temp.y++;
			legalMove.push_back(temp);
		}
		break;

	case 3: //黑象
		if (temp.x - 2 >= 0 && temp.y - 2 >= 0) //向左上
		{
			temp.x = temp.x - 2;
			temp.y = temp.y - 2;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.x + 2 <= 8 && temp.y - 2 >= 0) //向右上
		{
			temp.x = temp.x + 2;
			temp.y = temp.y - 2;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.x - 2 >= 0 && temp.y + 2 <= 4) //向左下
		{
			temp.x = temp.x - 2;
			temp.y = temp.y + 2;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.x + 2 <= 8 && temp.y + 2 <= 4) //向右下
		{
			temp.x = temp.x + 2;
			temp.y = temp.y + 2;
			legalMove.push_back(temp);
		}
		break;

	case 4: //黑車
		while (temp.x > 0) //向左
		{
			temp.x--;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		while (temp.x < 8) //向右
		{
			temp.x++;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		while (temp.y > 0) //向上
		{
			temp.y--;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		while (temp.y < 9) //向下
		{
			temp.y++;
			legalMove.push_back(temp);
		}
		break;

	case 5: //黑馬
		break;

	case 6: //黑包
		break;

	case 7: //黑卒
		break;

	case 8: //紅帥
		if (temp.x > 3) //向左
		{
			temp.x--;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.x < 5) //向右
		{
			temp.x++;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.y > 7) //向上
		{
			temp.y--;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.y < 9) //向下
		{
			temp.y++;
			legalMove.push_back(temp);
		}
		break;

	case 9: //紅仕
		if (temp.x > 3 && temp.y > 7) //向左上
		{
			temp.x--;
			temp.y--;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.x < 5 && temp.y > 7) //向右上
		{
			temp.x++;
			temp.y--;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.x > 3 && temp.y < 9) //向左下
		{
			temp.x--;
			temp.y++;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.x < 5 && temp.y < 9) //向右下
		{
			temp.x++;
			temp.y++;
			legalMove.push_back(temp);
		}
		break;

	case 10: //紅相
		if (temp.x - 2 >= 0 && temp.y - 2 >= 5) //向左上
		{
			temp.x = temp.x - 2;
			temp.y = temp.y - 2;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.x + 2 <= 8 && temp.y - 2 >= 5) //向右上
		{
			temp.x = temp.x + 2;
			temp.y = temp.y - 2;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.x - 2 >= 0 && temp.y + 2 <= 9) //向左下
		{
			temp.x = temp.x - 2;
			temp.y = temp.y + 2;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		if (temp.x + 2 <= 8 && temp.y + 2 <= 9) //向右下
		{
			temp.x = temp.x + 2;
			temp.y = temp.y + 2;
			legalMove.push_back(temp);
		}
		break;

	case 11: //紅車
		while (temp.x > 0) //向左
		{
			temp.x--;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		while (temp.x < 8) //向右
		{
			temp.x++;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		while (temp.y > 0) //向上
		{
			temp.y--;
			legalMove.push_back(temp);
		}
		temp = currentPosition;
		while (temp.y < 9) //向下
		{
			temp.y++;
			legalMove.push_back(temp);
		}
		break;

	case 12: //紅傌
		break;

	case 13: //紅炮
		break;

	case 14: //紅兵
		break;
	}
}

void Chess::clearLegalMove()
{
	legalMove.clear();
}

vector <position> Chess::getLegalMove()
{
	return legalMove;
}