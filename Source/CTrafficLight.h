#pragma once

#include "console.h"
#include <stdio.h>

#define GREEN_LIGHT		0
#define RED_LIGHT		1

class CTrafficLight {
private:
	bool light;
	int x;
	int y;

public:
	int count;

public:
	CTrafficLight() {
		light = GREEN_LIGHT;
		x = 0;
		y = 0;
		count = 0;
	}

	CTrafficLight(int x, int y) {
		this->light = GREEN_LIGHT;
		this->x = x;
		this->y = y;
		count = 0;
	}

	void setLight(bool l) {
		this->light = l;
	}

	void setX(int x) {
		this->x = x;
	}

	void setY(int y) {
		this->y = y;
	}

	bool getLight() {
		return this->light;
	}

	int getX() {
		return this->x;
	}

	int getY() {
		return this->y;
	}

	void draw() {
		if (this->light == RED_LIGHT) {
			Console::gotoXY(this->x, this->y);
			Console::TextColor(ColorCode_Red);
			printf("%c", 219);
			Console::gotoXY(x, y + 1);
			Console::TextColor(ColorCode_Grey);
			printf("%c", 219);
		}
		else {
			Console::gotoXY(this->x, this->y);
			Console::TextColor(ColorCode_Grey);
			printf("%c", 219);
			Console::gotoXY(x, y + 1);
			Console::TextColor(ColorCode_Green);
			printf("%c", 219);
		}
	}
};