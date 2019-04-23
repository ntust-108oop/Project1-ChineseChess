#pragma once
#include <vector>
using std::vector;

struct position
{
	int positionX;
	int positionY;
};

class Chess
{
public:
	Chess();
	~Chess();
	// 在讀棋盤文件的時候可以用
	Chess(int type, int posX, int posY);
	
	// Black:1~7 Red:8~14 
	int chessType;
	struct position currentPosition;
	vector<struct position> legalMove;

	// 當棋子被選到的時候，由chessboard來改變這個值
	bool chosen;
};

