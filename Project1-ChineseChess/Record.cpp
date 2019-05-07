#include "Record.h"
#include <Windows.h>
#include <iostream>
#include "Console.h"

vector<int> Record::chessTypeData;
vector<struct position> Record::fromPos;
vector<struct position> Record::toPos;
vector<int> Record::ifOnly;
short leftStart = 7, topStart = 4;

Record::Record()
{
}


Record::~Record()
{
}

void Record::printRecord()
{
	int count = 0;
	int i = 0;
	if (chessTypeData.size() > 9)
	{
		i = chessTypeData.size() - 10;
	}
	position storeCursor = getCursorPosition();

	while(i < chessTypeData.size())
	{
		position printPosition = { leftStart, topStart + count * 2 };
		SetPosition(printPosition);
		SetColor(0x07);	// 設成黑底白字
		std::cout << i + 1 << " ";
		count++;

		if(chessTypeData[i] <= 7)	// 黑
		{
			SetColor(0x08);
			std::cout << "黑" << " " ;
		}

		if(chessTypeData[i] > 7)	// 紅
		{
			SetColor(0x0c);
			std::cout << "紅" << " " ;
		}

		SetColor(0x07);
		if (ifOnly[i] == 0)			// 普通的情況
		{
			switch (chessTypeData[i])
			{
			case 1:
				std::cout << "：" << " " << "將" << " ";
				break;
			case 2:
				std::cout << "：" << " " << "士" << " ";
				break;
			case 3:
				std::cout << "：" << " " << "象" << " ";
				break;
			case 4:
				std::cout << "：" << " " << "車" << " ";
				break;
			case 5:
				std::cout << "：" << " " << "馬" << " ";
				break;
			case 6:
				std::cout << "：" << " " << "包" << " ";
				break;
			case 7:
				std::cout << "：" << " " << "卒" << " ";
				break;
			case 8:
				std::cout << "：" << " " << "帥" << " ";
				break;
			case 9:
				std::cout << "：" << " " << "仕" << " ";
				break;
			case 10:
				std::cout << "：" << " " << "相" << " ";
				break;
			case 11:
				std::cout << "：" << " " << "車" << " ";
				break;
			case 12:
				std::cout << "：" << " " << "傌" << " ";
				break;
			case 13:
				std::cout << "：" << " " << "炮" << " ";
				break;
			case 14:
				std::cout << "：" << " " << "兵" << " ";
				break;
			default:
				break;
			}

			if (chessTypeData[i] <= 7)		// 黑
			{
				switch (fromPos[i].x)
				{
				case 0:
					std::cout << "１" << " ";
					break;
				case 1:
					std::cout << "２" << " ";
					break;
				case 2:
					std::cout << "３" << " ";
					break;
				case 3:
					std::cout << "４" << " ";
					break;
				case 4:
					std::cout << "５" << " ";
					break;
				case 5:
					std::cout << "６" << " ";
					break;
				case 6:
					std::cout << "７" << " ";
					break;
				case 7:
					std::cout << "８" << " ";
					break;
				case 8:
					std::cout << "９" << " ";
					break;
				default:
					break;
				}

				int move = toPos[i].y - fromPos[i].y;
				if (move > 0)
				{
					std::cout << "進" << " ";
				}
				else if (move < 0)
				{
					std::cout << "退" << " ";
					move = -move;
				}
				else if (move == 0)
				{
					std::cout << "平" << " ";
					move = toPos[i].x + 1;
				}

				switch (move)
				{
				case 1:
					std::cout << "１";
					break;
				case 2:
					std::cout << "２";
					break;
				case 3:
					std::cout << "３";
					break;
				case 4:
					std::cout << "４";
					break;
				case 5:
					std::cout << "５";
					break;
				case 6:
					std::cout << "６";
					break;
				case 7:
					std::cout << "７";
					break;
				case 8:
					std::cout << "８";
					break;
				case 9:
					std::cout << "９";
					break;
				default:
					break;
				}

			}
			else if (chessTypeData[i] > 7)		// 紅
			{
				switch (fromPos[i].x)
				{
				case 0:
					std::cout << "一" << " ";
					break;
				case 1:
					std::cout << "二" << " ";
					break;
				case 2:
					std::cout << "三" << " ";
					break;
				case 3:
					std::cout << "四" << " ";
					break;
				case 4:
					std::cout << "五" << " ";
					break;
				case 5:
					std::cout << "六" << " ";
					break;
				case 6:
					std::cout << "七" << " ";
					break;
				case 7:
					std::cout << "八" << " ";
					break;
				case 8:
					std::cout << "九" << " ";
					break;
				default:
					break;
				}

				int move = toPos[i].y - fromPos[i].y;
				if (move > 0)
				{
					std::cout << "退" << " ";
				}
				else if (move < 0)
				{
					std::cout << "進" << " ";
					move = -move;
				}
				else if (move == 0)
				{
					std::cout << "平" << " ";
					move = toPos[i].x + 1;
				}

				switch (move)
				{
				case 1:
					std::cout << "一";
					break;
				case 2:
					std::cout << "二";
					break;
				case 3:
					std::cout << "三";
					break;
				case 4:
					std::cout << "四";
					break;
				case 5:
					std::cout << "五";
					break;
				case 6:
					std::cout << "六";
					break;
				case 7:
					std::cout << "七";
					break;
				case 8:
					std::cout << "八";
					break;
				case 9:
					std::cout << "九";
					break;
				default:
					break;
				}
			}
		}
		else		// 如果這個棋不是自己這條線上唯一的一個自己的種類，需要額外處理
		{



		}

		i++;
	}

	SetPosition(storeCursor);
	
}

void Record::saveThisStep(int chessType, int fromX, int fromY, int toX, int toY, int only)
{
	struct position from;
	struct position to;

	from.x = fromX;
	from.y = fromY;
	to.x = toX;
	to.y = toY;

	chessTypeData.push_back(chessType);
	fromPos.push_back(from);
	toPos.push_back(to);
	ifOnly.push_back(only);
	
}

void Record::clearRecord()
{
	chessTypeData.clear();
	fromPos.clear();
	toPos.clear();
}

