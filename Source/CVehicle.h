#pragma once

#define SPEED_CAR 2
#define SPEED_TRUCK 1

class CVehicle {
private:
	int _x, _y;
public:
	virtual void move() = 0;
	virtual void clear() = 0;
	virtual void draw() = 0;

	bool isTouchLeftMargin();
	bool isTouchRightMargin();
	int getX() const;
	int getY() const;
	void setX(int);
	void setY(int);
	void set(int, int);
};

class CTruck : public CVehicle {
public:
	void move();
	void clear();
	void draw();
};


class CCar : public CVehicle {
public:
	void move();
	void clear();
	void draw();
};
