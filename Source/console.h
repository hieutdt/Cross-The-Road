#pragma once

#include <Windows.h>

#define ColorCode_Black			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15

#define default_ColorCode		7


#define KEY_UP		72
#define KEY_DOWN	80
#define KEY_LEFT	75
#define KEY_RIGHT	77
#define Special_Key -32
#define Special_Key_2 224


class Console {
public:
	static void clrscr();
	static void gotoXY(int column, int line);
	static int whereX();
	static int whereY();
	static void TextColor(int color);
	static void ResizeConsoleWindow(int witdh, int height);
	static void HideConsolePointer();
	static void FixConsoleWindow();
	static void DrawBorder(int x, int y, int height, int width, int colorCode);
	static void DrawTable(int x, int y, int height, int width, int colorCode);
};