#include "console.h"
#include <stdio.h>

void Console::clrscr() {
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void Console::gotoXY(int column, int line) {
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Console::TextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Console::ResizeConsoleWindow(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void Console::HideConsolePointer() {
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

int Console::whereX() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}

int Console::whereY() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

void Console::FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void Console::DrawTable(int x, int y, int height, int width, int colorCode) {
	Console::TextColor(colorCode);
	for (int i = 0; i < height; i++) {		
		for (int j = 0; j < width; j++) {
			Console::gotoXY(x + j, y + i);
			printf(" ");
		}
	}
}

void Console::DrawBorder(int x, int y, int height, int width, int colorCode) {
	Console::TextColor(colorCode);
	Console::gotoXY(x, y);
	printf("%c", 218);
	for (int i = 0; i < width - 2; i++) {
		printf("%c", 196);
	}
	printf("%c", 191);
	for (int i = 1; i < height - 1; i++) {
		Console::gotoXY(x, y + i);
		printf("%c", 179);
		Console::gotoXY(x + width - 1, y + i);
		printf("%c", 179);
	}
	Console::gotoXY(x, y + height - 1);
	printf("%c", 192);
	for (int i = 0; i < width - 2; i++) {
		printf("%c", 196);
	}
	printf("%c", 217);
	Console::TextColor(ColorCode_DarkWhite);
}