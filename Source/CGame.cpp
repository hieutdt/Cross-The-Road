#include "CGame.h"
#include "console.h"
#include <conio.h>
#include <iostream>
#include <thread>

using namespace std;

CGame::CGame() {	
	this->_started = false;
	this->_bird.resize(EASY_RANK_BIRD_NUM);
	this->_dinausor.resize(EASY_RANK_DINAUSOR_NUM);
	this->_car.resize(EASY_RANK_CAR_NUM);
	this->_truck.resize(EASY_RANK_TRUCK_NUM);

	for (int i = 0; i < _bird.size(); i++) {
		this->_bird[i].setX(START_BIRD_X + 30 * i);
		this->_bird[i].setY(START_BIRD_Y);
	}

	for (int i = 0; i < _dinausor.size(); i++) {
		this->_dinausor[i].setX(START_DINAUSOR_X + 30 * i);
		this->_dinausor[i].setY(START_DINAUSOR_Y);
	}

	for (int i = 0; i < _car.size(); i++) 
		this->_car[i].set(START_CAR_X + 30 * i, START_CAR_Y);

	for (int i = 0; i < _truck.size(); i++)
		this->_truck[i].set(START_TRUCK_X + 20 * i, START_TRUCK_Y);

	this->_trafficLight[0].setY(FIRST_LIGHT_Y);
	this->_trafficLight[1].setY(FIRST_LIGHT_Y + 10);
}

CGame::~CGame() {
}

CPeople CGame::getPeople() {
	return this->_people;
}

void CGame::drawLine() {
	Console::TextColor(ColorCode_Green);
	Console::gotoXY(0, 0);
	for (int i = 0; i < 119; i++)
		printf("%c", 219);
	Console::gotoXY(0, 1);
	for (int i = 0; i < 119; i++)
		printf("%c", 219);
	Console::gotoXY(0, 2);
	for (int i = 0; i < 119; i++)
		printf("%c", 219);
	Console::TextColor(ColorCode_DarkWhite);
	for (int j = 0; j < 5; j++) {
		int y = 5 * j + TOP_SPACE;
		Console::gotoXY(0, y);
		for (int i = 0; i < 119; i++) {
			Console::gotoXY(i, y);
			printf("%c", LINE_CHARACTER);
		}
	}
}

void CGame::clearAnimal() {
	for (int i = 0; i < _bird.size(); i++)
		this->_bird[i].clear();
	for (int i = 0; i < _dinausor.size(); i++)
		this->_dinausor[i].clear();
}

void CGame::drawAnimal() {
	for (int i = 0; i < _bird.size(); i++)
		this->_bird[i].draw();
	for (int i = 0; i < _dinausor.size(); i++)
		this->_dinausor[i].draw();
}

void CGame::drawVehicle() {
	for (int i = 0; i < EASY_RANK_CAR_NUM; i++)
		this->_car[i].draw();
	for (int i = 0; i < EASY_RANK_TRUCK_NUM; i++)
		this->_truck[i].draw();
}

void CGame::clearVehicle() {
	for (int i = 0; i < EASY_RANK_CAR_NUM; i++)
		this->_car[i].clear();
	for (int i = 0; i < EASY_RANK_TRUCK_NUM; i++)
		this->_truck[i].clear();
}

void CGame::drawGame() {
	this->clearAnimal();
	this->clearVehicle();
	this->drawAnimal();
	this->drawVehicle();
}

void CGame::updatePosPeople(char &MOVING) {
	if (MOVING == 'W') {
		this->_people.clear();
		this->_people.up(2);
		this->_people.draw();
	}
	else if (MOVING == 'S') {
		this->_people.clear();
		this->_people.down(2);
		this->_people.draw();
	}
	else if (MOVING == 'A') {
		this->_people.clear();
		this->_people.left(2);
		this->_people.draw();
	}
	else if (MOVING == 'D') {
		this->_people.clear();
		this->_people.right(2);
		this->_people.draw();
	}
}

void CGame::exitGame(thread* t) {
	this->setStarted(false);
}

void CGame::updatePosAnimal() {
	for (int i = 0; i < _bird.size(); i++) {
		this->_bird[i].clear();
		this->_bird[i].move();
		this->_bird[i].draw();
	}
	for (int i = 0; i < _dinausor.size(); i++) {
		this->_dinausor[i].clear();
		this->_dinausor[i].move();
		this->_dinausor[i].draw();
	}
}

void CGame::updatePosVehicle() {
	for (int i = 0; i < EASY_RANK_CAR_NUM; i++) {
		this->_car[i].clear();
		this->_car[i].move();
		this->_car[i].draw();
	}
	for (int i = 0; i < EASY_RANK_TRUCK_NUM; i++) {
		this->_truck[i].clear();
		this->_truck[i].move();
		this->_truck[i].draw();
	}
}

void CGame::startGame(int level) {
	Console::TextColor(ColorCode_DarkWhite);
	system("cls");

	drawLine();
	drawGame();
	drawTrafficLight();
	getPeople().draw();
	Console::gotoXY(4, 1);
	Console::TextColor(164);
	printf("Game level: %d", level);
	Console::DrawBorder(10, 29, 3, CONSOLE_WIDTH - 10, ColorCode_DarkGreen);
	Console::TextColor(ColorCode_DarkWhite);
	Console::gotoXY(14, 30);
	printf("ESC: Exit");
	Console::gotoXY(40, 30);
	printf("L: Save game");
	Console::gotoXY(66, 30);
	printf("P: Pause game");
	Console::gotoXY(92, 30);
	printf("R: Resume game");

	this->_started = true;
}

bool CGame::isImpact() {
	if (this->getPeople().getY() == 21 || this->getPeople().getY() == 19) {
		for (int i = 0; i < EASY_RANK_TRUCK_NUM; i++) {
			if (abs(this->_truck[i].getX() - this->_people.getX()) <= 2) {
				this->_people.setState(PEOPLE_DEAD);
				return true;
			}
		}
	}
	else if (this->getPeople().getY() <= 17 && this->getPeople().getY() >= 13) {
		for (int i = 0; i < EASY_RANK_DINAUSOR_NUM; i++) {
			if (abs(this->_dinausor[i].getX() - this->_people.getX()) <= 2) {
				this->_people.setState(PEOPLE_DEAD);
				return true;
			}
		}
	}
	else if (this->getPeople().getY() == 11 || this->getPeople().getY() == 9) {
		for (int i = 0; i < EASY_RANK_CAR_NUM; i++) {
			if (abs(this->_car[i].getX() - this->_people.getX()) <= 2) {
				this->_people.setState(PEOPLE_DEAD);
				return true;
			}
		}
	}
	else if (this->getPeople().getY() == 5 || this->getPeople().getY() == 3) {
		for (int i = 0; i < EASY_RANK_BIRD_NUM; i++) {
			if (abs(this->_bird[i].getX() - this->_people.getX()) <= 2) {
				this->_people.setState(PEOPLE_DEAD);
				return true;
			}
		}
	}
	return false;
}

bool CGame::isWin() {
	if (this->getPeople().getY() <= 2)
		return true;
	return false;
}

void CGame::drawNotification(bool state) {
	const int X_space = 22;
	const int Y_space = 25;
	if (state == false) { //GAME LOSE
		Console::TextColor(224);
		for (int i = 0; i < 3; i++) {
			Console::gotoXY(X_space, Y_space + i);
			for (int j = 0; j < 40; j++) {
				printf(" ");
			}
		}
		Console::TextColor(228);
		Console::gotoXY(X_space + 15, Y_space + 1);
		printf("GAME OVER!");
		Console::TextColor(ColorCode_Cyan);
		Console::gotoXY(X_space + 7, Y_space + 3);
		printf("Press any key to continue...");
		Console::TextColor(ColorCode_DarkWhite);
	}
	else { //WIN
		Console::TextColor(224);
		for (int i = 0; i < 3; i++) {
			Console::gotoXY(X_space, Y_space + i);
			for (int j = 0; j < 40; j++) {
				printf(" ");
			}
		}
		Console::TextColor(226);
		Console::gotoXY(X_space + 13, Y_space + 1);
		printf("CONGRATULATIONS!");
		Console::TextColor(ColorCode_Cyan);
		Console::gotoXY(X_space + 7, Y_space + 3);
		printf("Press any key to continue...");
		Console::TextColor(ColorCode_DarkWhite);
	}
}

void CGame::drawTrafficLight() {
	this->_trafficLight[0].draw();
	this->_trafficLight[1].draw();
}

void CGame::setTrafficLight(bool l) {
	this->_trafficLight[0].setLight(l);
	this->_trafficLight[1].setLight(l);
}

bool CGame::getTrafficLight() {
	return this->_trafficLight[0].getLight();
}

bool CGame::isStarted() {
	return this->_started == true;
}

void CGame::drawName() {
	const int first_x = 25;
	Console::TextColor(ColorCode_Cyan);
	Console::gotoXY(first_x, 0);
	printf("___________________ ________    _________ _________.___ _______    ________ ");
	Console::gotoXY(first_x, 1);
	printf("\\_   ___ \\______   \\\\_____  \\  /   _____//   _____/|   |\\      \\  /  _____/ ");
	Console::gotoXY(first_x, 2);
	printf("/    \\  \\/|       _/ /   |   \\ \\_____  \\ \\_____  \\ |   |/   |   \\/   \\  ___ ");
	Console::gotoXY(first_x, 3);
	printf("\\     \\___|    |   \\/    |    \\/        \\/        \\|   /    |    \\    \\_\\  \\ ");
	Console::gotoXY(first_x, 4);
	printf(" \\______  /____|_  /\\_______  /_______  /_______  /|___\\____|__  /\\______  /");
	Console::gotoXY(first_x, 5);
	printf("        \\/       \\/         \\/        \\/        \\/             \\/        \\/ ");
	Console::gotoXY(first_x + 15, 6);
	printf("__________ ________      _____  ________   ");
	Console::gotoXY(first_x + 15, 7);
	printf("\\______   \\\\_____  \\    /  _  \\ \\______ \\  ");
	Console::gotoXY(first_x + 15, 8);
	printf(" |       _/ /   |   \\  /  /_\\  \\ |    |  \\ ");
	Console::gotoXY(first_x + 15, 9);
	printf(" |    |   \\/    |    \\/    |    \\|    `   \\ ");
	Console::gotoXY(first_x + 15, 10);
	printf(" |____|_  /\\_______  /\\____|__  /_______  /");
	Console::gotoXY(first_x + 15, 11);
	printf("        \\/         \\/         \\/        \\/");
	Console::TextColor(ColorCode_DarkWhite);
}

void CGame::setStarted(bool b) {
	this->_started = b;
}

void CGame::resetGame() {
	this->_people.reset();

	for (int i = 0; i < _bird.size(); i++) {
		this->_bird[i].setX(START_BIRD_X + 30 * i);
		this->_bird[i].setY(START_BIRD_Y);
	}

	for (int i = 0; i < _dinausor.size(); i++) {
		this->_dinausor[i].setX(START_DINAUSOR_X + 30 * i);
		this->_dinausor[i].setY(START_DINAUSOR_Y);
	}

	for (int i = 0; i < _car.size(); i++)
		this->_car[i].set(START_CAR_X + 30 * i, START_CAR_Y);

	for (int i = 0; i < _truck.size(); i++)
		this->_truck[i].set(START_TRUCK_X + 20 * i, START_TRUCK_Y);

	this->_trafficLight[0].setY(FIRST_LIGHT_Y);
	this->_trafficLight[1].setY(FIRST_LIGHT_Y + 10);
}

void CGame::saveGame(std::ofstream &out, int curLevel, int trafficCount) {
	//Dong dau tien ghi level hien tai
	out.write(reinterpret_cast<const char *>(&curLevel), sizeof(int));
	//Dong tiep theo ghi so dem cua den giao thong
	out.write(reinterpret_cast<const char *> (&trafficCount), sizeof(int));
	//Dong tiep theo ghi toa do CPeople
	int px, py;
	px = getPeople().getX();
	py = getPeople().getY();
	out.write(reinterpret_cast<const char *> (&px), sizeof(int));
	out.write(reinterpret_cast<const char *>(&py), sizeof(int));
	//Toa do cua nhung con chim hoa mi
	for (int i = 0; i < EASY_RANK_BIRD_NUM; i++) {
		int x, y;
		x = this->_bird[i].getX();
		y = this->_bird[i].getY();
		out.write(reinterpret_cast<const char *>(&x), sizeof(int));
		out.write(reinterpret_cast<const char *>(&y), sizeof(int));
	}
	//Toa do cua nhung con khung long 
	for (int i = 0; i < EASY_RANK_DINAUSOR_NUM; i++) {
		int x, y;
		x = this->_dinausor[i].getX();
		y = this->_dinausor[i].getY();
		out.write(reinterpret_cast<const char *>(&x), sizeof(int));
		out.write(reinterpret_cast<const char *>(&y), sizeof(int));
	}
	//Toa do cua nhung chiec xe audi
	for (int i = 0; i < EASY_RANK_CAR_NUM; i++) {
		int x, y;
		x = this->_car[i].getX();
		y = this->_car[i].getY();
		out.write(reinterpret_cast<const char *>(&x), sizeof(int));
		out.write(reinterpret_cast<const char *>(&y), sizeof(int));
	}
	//Toa do cua nhung Optimus
	for (int i = 0; i < EASY_RANK_TRUCK_NUM; i++) {
		int x, y;
		x = this->_truck[i].getX();
		y = this->_truck[i].getY();
		out.write(reinterpret_cast<const char *>(&x), sizeof(int));
		out.write(reinterpret_cast<const char *>(&y), sizeof(int));
	}
}

void CGame::loadGame(std::ifstream& in, int &level, int& countingTrafficLight) {
	in.read(reinterpret_cast<char*> (&level), sizeof(int));
	in.read(reinterpret_cast<char *> (&countingTrafficLight), sizeof(int));
	int px, py;
	in.read(reinterpret_cast<char*> (&px), sizeof(int));
	in.read(reinterpret_cast<char*> (&py), sizeof(int));
	this->_people.setX(px);
	this->_people.setY(py);
	for (int i = 0; i < EASY_RANK_BIRD_NUM; i++) {
		int x, y;
		in.read(reinterpret_cast<char*> (&x), sizeof(int));
		in.read(reinterpret_cast<char*> (&y), sizeof(int));
		this->_bird[i].set(x, START_BIRD_Y);
	}

	for (int i = 0; i < EASY_RANK_DINAUSOR_NUM; i++) {
		int x, y;
		in.read(reinterpret_cast<char*> (&x), sizeof(int));
		in.read(reinterpret_cast<char*> (&y), sizeof(int));
		this->_dinausor[i].set(x, START_DINAUSOR_Y);
	}

	for (int i = 0; i < EASY_RANK_CAR_NUM; i++) {
		int x, y;
		in.read(reinterpret_cast<char*> (&x), sizeof(int));
		in.read(reinterpret_cast<char*> (&y), sizeof(int));
		this->_car[i].set(x, START_CAR_Y);
	}

	for (int i = 0; i < EASY_RANK_TRUCK_NUM; i++) {
		int x, y;
		in.read(reinterpret_cast<char*> (&x), sizeof(int));
		in.read(reinterpret_cast<char*> (&y), sizeof(int));
		this->_truck[i].set(x, START_TRUCK_Y);
	}
}

void CGame::pauseGame() {
	this->setStarted(false);
}

void CGame::remuseGame() {
	this->setStarted(true);
}

int CGame::getTrafficLightCount() {
	return this->_trafficLight->count;
}

void CGame::setTrafficLightCount(int n) {
	this->_trafficLight->count = n;
}