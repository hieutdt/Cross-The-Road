#include "CVehicle.h"
#include "console.h"
#include <iostream>
#include "CGame.h"

using namespace std;

int CVehicle::getX() const {
	return this->_x;
}

int CVehicle::getY() const {
	return this->_y;
}

void CVehicle::set(int x, int y) {
	this->_x = x;
	this->_y = y;
}

void CVehicle::setX(int x) {
	this->_x = x;
}

void CVehicle::setY(int y) {
	this->_y = y;
}


bool CVehicle::isTouchLeftMargin() {
	return this->getX() <= 1;
}

bool CVehicle::isTouchRightMargin() {
	return this->getX() >= CONSOLE_WIDTH;
}

//----------------------------------------
//Car
//----------------------------------------

void CCar::move() {
	if (!isTouchRightMargin())
		this->setX(this->getX() + SPEED_CAR);
	else
		this->setX(1);
}

void CCar::clear() {
	Console::gotoXY(this->getX(), this->getY());
	printf("     ");
	Console::gotoXY(this->getX(), this->getY() + 1);
	printf("     ");
}

void CCar::draw() {
	Console::TextColor(ColorCode_Red);
	Console::gotoXY(this->getX(), this->getY());
	printf(" %c%c%c", 220, 220, 220);
	Console::TextColor(ColorCode_DarkRed);
	Console::gotoXY(this->getX(), this->getY() + 1);
	printf("%c%c%c%c%c",220,  219, 219, 219, 220);
	Console::TextColor(ColorCode_DarkWhite);
}

//-----------------------------------------
//Truck
//-----------------------------------------

void CTruck::move() {
	if (getX() > SPEED_TRUCK)
		this->set(this->getX() - SPEED_TRUCK, this->getY());
	else
		this->setX(CONSOLE_WIDTH);
}

void CTruck::clear() {
	Console::gotoXY(this->getX(), this->getY());
	printf("      ");
	Console::gotoXY(this->getX(), this->getY() + 1);
	printf("      ");
}


void CTruck::draw() {
	Console::TextColor(ColorCode_DarkYellow);
	Console::gotoXY(this->getX(), this->getY());
	printf("  %c%c%c%c", 219, 219, 219, 219);
	Console::gotoXY(this->getX(), this->getY() + 1);
	Console::TextColor(ColorCode_Blue);
	printf("%c%c", 219, 219);
	Console::TextColor(ColorCode_DarkYellow);
	printf("%c%c%c%c", 219, 219, 219, 219);
	Console::TextColor(ColorCode_DarkWhite);
}