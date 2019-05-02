#include "ChessBoard.h"
#include <Windows.h>


ChessBoard::ChessBoard()
{
	//開局初始化
	turns = 1;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 9; j++)
			wholePosition[j][i] = NULL;

	//指標賦值
	wholePosition[0][0] = new Chess(4, 0, 0);
	wholePosition[1][0] = new Chess(5, 1, 0);
	wholePosition[2][0] = new Chess(3, 2, 0);
	wholePosition[3][0] = new Chess(2, 3, 0);
	wholePosition[4][0] = new Chess(1, 4, 0);
	wholePosition[5][0] = new Chess(2, 5, 0);
	wholePosition[6][0] = new Chess(3, 6, 0);
	wholePosition[7][0] = new Chess(5, 7, 0);
	wholePosition[8][0] = new Chess(4, 8, 0);
	wholePosition[1][2] = new Chess(6, 1, 2);
	wholePosition[7][2] = new Chess(6, 7, 2);
	wholePosition[0][3] = new Chess(7, 0, 3);
	wholePosition[2][3] = new Chess(7, 2, 3);
	wholePosition[4][3] = new Chess(7, 4, 3);
	wholePosition[6][3] = new Chess(7, 6, 3);
	wholePosition[8][3] = new Chess(7, 8, 3);

	wholePosition[0][9] = new Chess(11, 0, 9);
	wholePosition[1][9] = new Chess(12, 1, 9);
	wholePosition[2][9] = new Chess(10, 2, 9);
	wholePosition[3][9] = new Chess(9, 3, 9);
	wholePosition[4][9] = new Chess(8, 4, 9);
	wholePosition[5][9] = new Chess(9, 5, 9);
	wholePosition[6][9] = new Chess(10, 6, 9);
	wholePosition[7][9] = new Chess(12, 7, 9);
	wholePosition[8][9] = new Chess(11, 8, 9);
	wholePosition[1][7] = new Chess(6, 1, 7);
	wholePosition[7][7] = new Chess(6, 7, 7);
	wholePosition[0][6] = new Chess(7, 0, 6);
	wholePosition[2][6] = new Chess(7, 2, 6);
	wholePosition[4][6] = new Chess(7, 4, 6);
	wholePosition[6][6] = new Chess(7, 6, 6);
	wholePosition[8][6] = new Chess(7, 8, 6);
}

ChessBoard::~ChessBoard()
{
}

ChessBoard::ChessBoard(string fileTxt)
{	
	readTheBoard(fileTxt);
}


void ChessBoard::printThePlane()
{
//    for (int i = 5; i < 40; i++) // 測試排版：清一塊空白的區域
//    {
//        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(42),static_cast<short>(i) });
//        for (int j = 0; j < 65; j++)
//        {
//            cout << " ";
//        }
//    }
//    
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < 9; j++)
//		{
//            // 測試排版
//            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(50+j*5),static_cast<short>(2+i*4) });
//
//			if(wholePosition[j][i]!=NULL)cout << wholePosition[j][i]->getChessType() << "\t";
//			else cout << "0\t";
//		}
//		 cout << "\n";
//	}
//    // 因為畫框框會被影響所以稍微寫一下
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(50),static_cast<short>(42) });
//	 
//    cout << turns << "\n";
//}

void ChessBoard::printChosenPlane()
{
	for (int i = 5; i < 40; i++) // 測試排版：清一塊空白的區域
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(42),static_cast<short>(i) });
		for (int j = 0; j < 65; j++)
		{
			cout << " ";
		}
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			// 測試排版
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(50 + j * 5),static_cast<short>(2 + i * 4) });
			
			position tmp;
			tmp.x = j;
			tmp.y = i;
			//從legalMove中找到可以走的位置，改變顏色配置
			vector<position>::iterator it = find(legalMove.begin(), legalMove.end(), tmp);
			if(it!= legalMove.end()) SetColor(112);
			else SetColor();
			if (wholePosition[j][i] != NULL)cout << wholePosition[j][i]->getChessType() << "\t";
			else cout << "0\t";
		}
		cout << "\n";
	}
	// 因為畫框框會被影響所以稍微寫一下
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(50),static_cast<short>(42) });

	cout << turns << "\n";
}

void ChessBoard::moveTheChess(int fromX, int fromY, int toX, int toY)
{
	if (wholePosition[toX][toY] != NULL)
	{
		delete wholePosition[toX][toY];
		wholePosition[toX][toY] = wholePosition[fromX][fromY];
		wholePosition[fromX][fromY] = NULL;
	}
	else
	{
		wholePosition[toX][toY] = wholePosition[fromX][fromY];
		wholePosition[fromX][fromY] = NULL;
	}
}

void ChessBoard::readTheBoard(string fileTxt)
{
	//開檔讀取並新建所需的棋子
	fstream file(fileTxt);
	if (file.is_open())
	{
		//丟掉現存的棋盤內容
		/*待補record部分的清除*/
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 9; j++)
				if (wholePosition[j][i] != NULL)
				{
					delete wholePosition[j][i];
					wholePosition[j][i] = NULL;
				}
		}

		int tmp;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				file >> tmp;
				if (tmp != 0)wholePosition[j][i] = new Chess(tmp, j, i);
			}
		}
		file >> turns;
	}
	file.close();
	file.clear();
}

void ChessBoard::saveTheBoard(string fileTxt)
{
	fstream file(fileTxt);
	if (file.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				wholePosition[j][i] == NULL ? file << wholePosition[j][i]->getChessType() : file << '0';
				file << ' ';
			}
			file << '\n';
		}
		file << turns;
	}
	file.close();
	file.clear();
}

void ChessBoard::saveTheBoard()
{
	fstream file;
	file.open("file.txt", ios::trunc);
	if (file.is_open())
	{
		file.clear();
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				wholePosition[j][i] == NULL ? file << wholePosition[j][i]->getChessType() : file << '0';
				file << ' ';
			}
			file << '\n';
		}
		file >> turns;
	}
	file.close();
	file.clear();
}

void ChessBoard::manageLegalMove(int x, int y)
{
	position temp = wholePosition[x][y]->getCurrentPosition();
	switch (wholePosition[x][y]->getChessType())
		{
		case 1: //黑將
			if (temp.x > 3) //向左
			{
				temp.x--;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x < 5) //向右
			{
				temp.x++;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.y > 7) //向上
			{
				temp.y--;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.y < 9) //向下
			{
				temp.y++;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			// 王不見王
			while (temp.y > 0)
			{
				temp.y--;
				if (wholePosition[temp.x][temp.y] != NULL)
				{
					// 若是中間被擋住就沒事
					if (wholePosition[temp.x][temp.y]->getChessType() != 8)
					{
						break;
					}
					else
					{
						legalMove.push_back(temp);
						break;
					}
				}
			}
			break;

		case 2: //黑士
			if (temp.x > 3 && temp.y > 7) //向左上
			{
				temp.x--;
				temp.y--;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x < 5 && temp.y > 7) //向右上
			{
				temp.x++;
				temp.y--;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x > 3 && temp.y < 9) //向左下
			{
				temp.x--;
				temp.y++;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x < 5 && temp.y < 9) //向右下
			{
				temp.x++;
				temp.y++;
				legalMove.push_back(temp);
			}
			break;

		case 3: //黑象
			if (temp.x - 2 >= 0 && temp.y - 2 >= 5 && (wholePosition[x - 1][y - 1] == NULL)) //向左上
			{
				temp.x -= 2;
				temp.y -= 2;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x + 2 <= 8 && temp.y - 2 >= 5 && (wholePosition[x + 1][y - 1] == NULL)) //向右上
			{
				temp.x += 2;
				temp.y -= 2;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x - 2 >= 0 && temp.y + 2 <= 9 && (wholePosition[x - 1][y + 1] == NULL)) //向左下
			{
				temp.x -= 2;
				temp.y += 2;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x + 2 <= 8 && temp.y + 2 <= 9 && (wholePosition[x + 1][y + 1] == NULL)) //向右下
			{
				temp.x += 2;
				temp.y += 2;
				legalMove.push_back(temp);
			}
			break;


		case 4:  //黑車
		case 11: //紅車
			while (temp.x > 0) //向左
			{
				temp.x--;
				legalMove.push_back(temp);
			}
			temp = wholePosition[x][y]->getCurrentPosition();
			while (temp.x < 8) //向右
			{
				temp.x++;
				legalMove.push_back(temp);
			}
			temp = wholePosition[x][y]->getCurrentPosition();
			while (temp.y > 0) //向上
			{
				temp.y--;
				legalMove.push_back(temp);
			}
			temp = wholePosition[x][y]->getCurrentPosition();
			while (temp.y < 9) //向下
			{
				temp.y++;
				legalMove.push_back(temp);
			}
			break;

		case 5: //黑馬
		case 12: //紅傌
			if (temp.x - 2 >= 0 && temp.y - 1 >= 0 && wholePosition[temp.x - 1][temp.y] == NULL) //向 10 點鐘方向
			{
				temp.x = temp.x - 2;
				temp.y--;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x - 1 >= 0 && temp.y - 2 >= 0 && wholePosition[temp.x][temp.y - 1] == NULL) //向 11 點鐘方向
			{
				temp.x--;
				temp.y = temp.y - 2;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x + 1 <= 8 && temp.y - 2 >= 0 && wholePosition[temp.x][temp.y - 1] == NULL) //向 1 點鐘方向
			{
				temp.x++;
				temp.y = temp.y - 2;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x + 2 <= 8 && temp.y - 1 >= 0 && wholePosition[temp.x + 1][temp.y] == NULL) //向 2 點鐘方向
			{
				temp.x = temp.x + 2;
				temp.y--;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x + 2 <= 8 && temp.y + 1 <= 9 && wholePosition[temp.x + 1][temp.y] == NULL) //向 4 點鐘方向
			{
				temp.x = temp.x + 2;
				temp.y++;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x + 1 <= 8 && temp.y + 2 <= 9 && wholePosition[temp.x][temp.y + 1] == NULL) //向 5 點鐘方向
			{
				temp.x++;
				temp.y = temp.y + 2;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x - 1 >= 0 && temp.y + 2 <= 9 && wholePosition[temp.x][temp.y + 1] == NULL) //向 7 點鐘方向
			{
				temp.x--;
				temp.y = temp.y + 2;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x - 2 >= 0 && temp.y + 1 <= 9 && wholePosition[temp.x - 1][temp.y] == NULL) //向 8 點鐘方向
			{
				temp.x = temp.x - 2;
				temp.y++;
				legalMove.push_back(temp);
			}
			break;

		case 6: //黑包
		case 13: //紅炮
			while (temp.x > 0) //向左
			{
				temp.x--;
				legalMove.push_back(temp);
				if (wholePosition[temp.x][temp.y] != NULL)
				{
					break;
				}
			}
			while (temp.x > 0)  // 取得可以吃的那一個
			{
				temp.x--;
				if (wholePosition[temp.x][temp.y] != NULL)
				{
					legalMove.push_back(temp);
					break;
				}
			}
			temp = wholePosition[x][y]->getCurrentPosition();

			while (temp.x < 8) //向右
			{
				temp.x++;
				legalMove.push_back(temp);
				if (wholePosition[temp.x][temp.y] != NULL)
				{
					break;
				}
			}
			while (temp.x < 8)
			{
				temp.x++;
				if (wholePosition[temp.x][temp.y] != NULL)
				{
					legalMove.push_back(temp);
					break;
				}
			}
			temp = wholePosition[x][y]->getCurrentPosition();

			while (temp.y > 0) //向上
			{
				temp.y--;
				legalMove.push_back(temp);
				if (wholePosition[temp.x][temp.y] != NULL)
				{
					break;
				}
			}
			while (temp.y > 0)
			{
				temp.y--;
				if (wholePosition[temp.x][temp.y] != NULL)
				{
					legalMove.push_back(temp);
					break;
				}
			}
			temp = wholePosition[x][y]->getCurrentPosition();
			
			while (temp.y < 9) //向下
			{
				temp.y++;
				legalMove.push_back(temp);
				if (wholePosition[temp.x][temp.y] != NULL)
				{
					break;
				}
			}
			while (temp.y < 9)
			{
				temp.y++;
				if (wholePosition[temp.x][temp.y] != NULL)
				{
					legalMove.push_back(temp);
					break;
				}
			}
			break;

		case 7: //黑卒
			if (temp.y >= 5) //在己方範圍，只能向下
			{
				temp.y--;
				legalMove.push_back(temp);
			}
			else //在敵方範圍
			{
				if (temp.x > 0) //向左
				{
					temp.x--;
					legalMove.push_back(temp);
					temp = wholePosition[x][y]->getCurrentPosition();
				}
				if (temp.x < 8) //向右
				{
					temp.x++;
					legalMove.push_back(temp);
					temp = wholePosition[x][y]->getCurrentPosition();
				}
				if (temp.y > 0) //向下
				{
					temp.y--;
					legalMove.push_back(temp);
				}
			}
			break;

		case 8: //紅帥
			if (temp.x > 3) //向左
			{
				temp.x--;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x < 5) //向右
			{
				temp.x++;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.y > 0) //向下
			{
				temp.y--;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.y < 2) //向上
			{
				temp.y++;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			// 王不見王
			while (temp.y < 9)
			{
				temp.y++;
				if (wholePosition[temp.x][temp.y] != NULL)
				{
					// 若是中間被擋住就沒事
					if (wholePosition[temp.x][temp.y]->getChessType() != 8)
					{
						break;
					}
					else
					{
						legalMove.push_back(temp);
						break;
					}
				}
			}
			break;
			
		case 9: //紅仕
			if (temp.x > 3 && temp.y > 0) //向左上
			{
				temp.x--;
				temp.y--;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x < 5 && temp.y > 0) //向右上
			{
				temp.x++;
				temp.y--;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x > 3 && temp.y < 2) //向左下
			{
				temp.x--;
				temp.y++;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x < 5 && temp.y < 2) //向右下
			{
				temp.x++;
				temp.y++;
				legalMove.push_back(temp);
			}
			break;

		case 10: //紅相
			if (temp.x - 2 >= 0 && temp.y - 2 >= 0 && (wholePosition[x - 1][y - 1] == NULL)) //向左下
			{
				temp.x = temp.x - 2;
				temp.y = temp.y - 2;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x + 2 <= 8 && temp.y - 2 >= 0 && (wholePosition[x + 1][y - 1] == NULL)) //向右下
			{
				temp.x = temp.x + 2;
				temp.y = temp.y - 2;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x - 2 >= 0 && temp.y + 2 <= 4 && (wholePosition[x - 1][y + 1] == NULL)) //向左上
			{
				temp.x = temp.x - 2;
				temp.y = temp.y + 2;
				legalMove.push_back(temp);
				temp = wholePosition[x][y]->getCurrentPosition();
			}
			if (temp.x + 2 <= 8 && temp.y + 2 <= 4 && (wholePosition[x + 1][y + 1] == NULL)) //向右上
			{
				temp.x = temp.x + 2;
				temp.y = temp.y + 2;
				legalMove.push_back(temp);
			}
			break;

		case 14: //紅兵
			if (temp.y <= 4) //在己方範圍，只能向上
			{
				temp.y++;
				legalMove.push_back(temp);
			}
			else //在敵方範圍
			{
				if (temp.x > 0) //向左
				{
					temp.x--;
					legalMove.push_back(temp);
					temp = wholePosition[x][y]->getCurrentPosition();
				}
				if (temp.x < 8) //向右
				{
					temp.x++;
					legalMove.push_back(temp);
					temp = wholePosition[x][y]->getCurrentPosition();
				}
				if (temp.y < 9) //向上
				{
					temp.y++;
					legalMove.push_back(temp);
				}
			}
			break;
		}




}

void ChessBoard::clearLegalMove()
{
	legalMove.clear();
}

void ChessBoard::SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
