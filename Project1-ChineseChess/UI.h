#ifndef UI_H
#define UI_H

#include <windows.h>
#include <conio.h>

typedef struct cursorPos 
{
	int x;
	int y;
} cursorPos;

class UI
{
public:
	UI();
	~UI();

	static void printUI();
	static void showMenu();

	// 取得當前游標位置
	static cursorPos getCursorPos();

    // 設定當前輸出底色
    static void SetColor(int = 7);
    // 設定游標位置
    static void SetPosition(cursorPos);

private:
    // 當前輸出底色
    static int color;
    // 當前游標位置
    static cursorPos cursorPosition;
};

#endif // !UI_H

