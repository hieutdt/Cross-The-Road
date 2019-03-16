#pragma once

#include "CVehicle.h"
#include "CAnimal.h"

#define PEOPLE_LIVE 0
#define PEOPLE_DEAD 1

class CPeople {
	int _x, _y;
	int _state; //trang thai song chet
public:
	CPeople();
	void up(int);
	void left(int);
	void right(int);
	void down(int);

	int getX();
	int getY();
	void setX(int);
	void setY(int);

	void setState(int);

	void draw();
	void clear();
	void reset();

	bool isDead() const;
};