#include "CPeople.h"
#include "console.h"
#include <iostream>
#include "CGame.h"

using namespace std;

CPeople::CPeople() {
	this->_x = 50;
	this->_y = 25;
	this->_state = PEOPLE_LIVE;
}

int CPeople::getX() {
	return this->_x;
}

int CPeople::getY() {
	return this->_y;
}

void CPeople::draw() {
	if (!this->isDead()) {
		//In dau
		Console::gotoXY(this->_x, this->_y);
		Console::TextColor(ColorCode_DarkRed);
		printf("%c%c%c", 220, 220, 220);
		Console::TextColor(14);
		Console::gotoXY(this->_x, this->_y + 1);
		printf("%c%c%c", 219, 219, 219);
		//In than
		Console::gotoXY(this->_x, this->_y + 2);
		printf("/");
		Console::TextColor(ColorCode_Cyan);
		printf("%c", 219);
		Console::TextColor(14);
		printf("\\");
		Console::TextColor(ColorCode_DarkWhite);
	}
	else {
		Console::TextColor(ColorCode_DarkRed);
		Console::gotoXY(this->_x, this->_y);
		printf("%c%c%c", 220, 220, 220);
		Console::gotoXY(this->_x, this->_y + 1);
		printf("%c%c%c", 219, 219, 219);
		Console::gotoXY(this->_x, this->_y + 2);
		printf("/%c\\", 219);
	}
}

bool CPeople::isDead() const {
	return this->_state == PEOPLE_DEAD;
}

void CPeople::up(int s) {
	this->_y -= s;
}

void CPeople::down(int s) {
	if (this->_y < 25)
		this->_y += s;
}

void CPeople::left(int s) {
	this->_x -= s;
}

void CPeople::right(int s) {
	this->_x += s;
}

void CPeople::setState(int st) {
	this->_state = st;
}

void CPeople::clear() {
	//Xoa dau
	Console::gotoXY(this->_x , this->_y);
	if (this->_y == 8 || this->_y == 13 || this->_y == 18 || this->_y == 23 || this->_y == 3)
		printf("%c%c%c", LINE_CHARACTER, LINE_CHARACTER, LINE_CHARACTER);
	else
		printf("    ");
	Console::gotoXY(this->_x, this->_y + 1);
	if (this->_y + 1 == 8 || this->_y + 1 == 13 || this->_y + 1 == 18 ||
		this->_y + 1 == 23 || this->_y + 1 == 3)
		printf("%c%c%c", LINE_CHARACTER, LINE_CHARACTER, LINE_CHARACTER);
	else
		printf("    ");
	//Xoa than
	Console::gotoXY(this->_x, this->_y + 2);
	if (this->_y + 2 == 8 || this->_y + 2 == 13 || this->_y + 2 == 18 ||
		this->_y + 2 == 23 || this->_y + 2 == 3)
		printf("%c%c%c", LINE_CHARACTER, LINE_CHARACTER, LINE_CHARACTER);
	else
		printf("    ");
}

void CPeople::reset() {
	this->_x = 50;
	this->_y = 25;
	this->_state = PEOPLE_LIVE;
}

void CPeople::setX(int x) {
	this->_x = x;
}

void CPeople::setY(int y) {
	this->_y = y;
}