#pragma once
#include <vector>
using std::vector;

struct position
{
	int x;
	int y;
};

class Chess
{
private:
	struct position currentPosition;		// 這個棋的當前位置
	// Black:1~7 Red:8~14 
	int chessType;
	vector<struct position> legalMove;

public:
	Chess();
	~Chess();
	// 在讀棋盤文件的時候可以用
	Chess(int type, int posX, int posY);
	
	
	void changePosition(int x, int y);
	

	// 當棋子被選到的時候，由chessboard來改變這個值
	// 選到的時候使所有legalmove變色也是由他做
	bool chosen;
};

