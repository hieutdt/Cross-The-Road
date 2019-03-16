#include "CAnimal.h"
#include "console.h"
#include "stdio.h"
#include "CGame.h"

int CAnimal::getX() const {
	return this->_x;
}

int CAnimal::getY() const {
	return this->_y;
}

void CAnimal::setX(int x) {
	this->_x = x;
}

void CAnimal::setY(int y) {
	this->_y = y;
}

void CAnimal::set(int x, int y) {
	this->_x = x;
	this->_y = y;
}


bool CAnimal::isTouchLeftMargin() {
	return this->getX() <= 1;
}

bool CAnimal::isTouchRightMargin() {
	return this->getX() >= CONSOLE_WIDTH;
}

//-------------------------------------------
// Bird
//-------------------------------------------

void CBird::move() {
	if (getX() > SPEED_BIRD)
		this->set(this->getX() - SPEED_BIRD, START_BIRD_Y);
	else
		this->set(CONSOLE_WIDTH, START_BIRD_Y);
}

void CBird::clear() {
	Console::gotoXY(this->getX(), this->getY());
	printf("    ");
	Console::gotoXY(this->getX(), this->getY() + 1);
	printf("    ");
}

void CBird::tell() {
	
}

void CBird::draw() {
	Console::gotoXY(this->getX(), this->getY());
	Console::TextColor(ColorCode_Blue);
	printf("%c %c", 220, 220);
	Console::gotoXY(this->getX(), this->getY() + 1);
	Console::TextColor(ColorCode_DarkGreen);
	printf(" %c ", 219);
	Console::TextColor(ColorCode_DarkWhite);
}


//--------------------------------------------
//Dinausor
//--------------------------------------------

void CDinausor::move() {
	if (!isTouchRightMargin())
		this->set(this->getX() + SPEED_DINAUSOR, START_DINAUSOR_Y);
	else
		this->set(1, START_DINAUSOR_Y);
}

void CDinausor::clear() {
	Console::gotoXY(this->getX(), this->getY());
	printf("     ");
	Console::gotoXY(this->getX(), this->getY() + 1);
	printf("     ");
	Console::gotoXY(this->getX(), this->getY() + 2);
	printf("     ");
}

void CDinausor::tell() {

}

void CDinausor::draw() {
	Console::gotoXY(this->getX(), this->getY());
	Console::TextColor(ColorCode_DarkYellow);
	printf("   %c%c", 219, 220);
	Console::TextColor(ColorCode_Grey);
	Console::gotoXY(this->getX(), this->getY() + 1);
	printf(" %c%c", 219, 219);
	Console::gotoXY(this->getX(), this->getY() + 2);
	printf("%c%c%c", 220, 219, 219);
	Console::TextColor(ColorCode_DarkWhite);
}

