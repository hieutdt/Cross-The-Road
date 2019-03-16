#pragma once

#define SPEED_BIRD 2
#define SPEED_DINAUSOR 1

class CAnimal {
private:
	int _x, _y;

public:
	virtual void move() {}
	virtual void tell() {}
	virtual void clear() {}
	virtual void draw() {}
	bool isTouchLeftMargin();
	bool isTouchRightMargin();

	int getX() const;
	int getY() const;
	void setX(int);
	void setY(int);
	void set(int, int);
};

class CDinausor : public CAnimal {
public:
	void move();
	void tell();
	void clear();
	void draw();
};

class CBird : public CAnimal {
public:
	void move();
	void tell();
	void clear();
	void draw();
};