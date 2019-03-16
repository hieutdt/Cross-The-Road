#pragma once

#include "console.h"
#include "CPeople.h"
#include "CVehicle.h"
#include "CAnimal.h"
#include "CTrafficLight.h"

#include <fstream>
#include <vector>
#include <thread>

using namespace std;

#define EASY_RANK_BIRD_NUM 4
#define EASY_RANK_DINAUSOR_NUM 3
#define EASY_RANK_TRUCK_NUM 5
#define EASY_RANK_CAR_NUM 4

#define CONSOLE_WIDTH 110
#define CONSOLE_HEIGHT 100

#define LINE_CHARACTER 221
#define TOP_SPACE 3

#define START_BIRD_X 1
#define START_BIRD_Y 5
#define START_DINAUSOR_X 1
#define START_DINAUSOR_Y 15
#define START_CAR_X 1
#define START_CAR_Y 10
#define START_TRUCK_X 1
#define START_TRUCK_Y 20

#define FIRST_LIGHT_X 0
#define FIRST_LIGHT_Y 9

class CGame {
private:
	CPeople _people;
	vector<CTruck> _truck;
	vector<CCar> _car;
	vector<CBird> _bird;
	vector<CDinausor> _dinausor;
	CTrafficLight _trafficLight[2];
	bool _started;

public:
	CGame();  //Chuan bi du lieu cho tat ca doi tuong
	~CGame(); //Huy tai nguyen cap phat

	void drawGame(); //Ve thu va xe
	void drawLine(); //Ve duong
	void drawName();

	void drawTrafficLight();
	void setTrafficLight(bool);
	bool getTrafficLight();

	int getTrafficLightCount();
	void setTrafficLightCount(int count);

	CPeople getPeople();

	bool isImpact();
	bool isWin();
	bool isStarted();
	void setStarted(bool);

	void clearAnimal();
	void drawAnimal();
	void clearVehicle();
	void drawVehicle();

	void resetGame();			//thiet lap lai toan bo du lieu nhu ban dau
	void exitGame(thread*);		//thoat Thread
	void startGame(int level);			//bat dau vao game
	void loadGame(std::ifstream&, int &level, int& countingTrafficLight);		//tai lai tro choi da luu
	void saveGame(std::ofstream&, int, int);		//luu game
	void pauseGame();	//tam dung Thread
	void remuseGame();	//quay lai Thread

	void updatePosPeople(char&); //thuc hien dieu khien di chuyen cua People
	void updatePosVehicle();	//thuc hien dieu khien di chuyen cua Vehicle
	void updatePosAnimal();		//thuc hien dieu khien di chuyen cua Animal

	void drawNotification(bool );
};
