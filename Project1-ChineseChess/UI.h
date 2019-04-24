#pragma once

static struct cursorPos 
{
	int x;
	int y;
};

class UI
{
public:
	UI();
	~UI();

	static void printUI();
	static void showMenu();

	// 取得當前游標位置
	static struct cursorPos getCursorPos();

};

