#include <iostream>
#include <conio.h>
#include <thread>
#include <fstream>
#include <string>
#include <filesystem>
#include <Windows.h>
#include <tchar.h>

#include "CGame.h"

using namespace std;

#pragma comment(lib, "winmm")

#define START_GAME_POS 15
#define LOAD_GAME_POS 19
#define SETTING_GAME_POS 23
#define EXIT_GAME_POS 27

#define LEVEL_1_SLEEP_TIME 80
#define LEVEL_2_SLEEP_TIME 60
#define LEVEL_3_SLEEP_TIME 50
#define LEVEL_4_SLEEP_TIME 40
#define LEVEL_5_SLEEP_TIME 30
#define LEVEL_6_SLEEP_TIME 20
#define LEVEL_7_SLEEP_TIME 10
#define LEVEL_8_SLEEP_TIME 5
#define LEVEL_9_SLEEP_TIME 3
#define LEVEL_10_SLEEP_TIME 1

#define GAME_LOSE 0
#define GAME_WIN 1
#define GAME_RUNNING 2
#define GAME_EXIT 3

CGame *game = new CGame();
bool IS_RUNNING = true;
char MOVING = ' ';
int sleepTime = LEVEL_1_SLEEP_TIME;
int gameState = GAME_RUNNING;
int curLevel = 1;
MCIERROR err;
bool SOUND_ON = true;

void exitGame(thread *t) {
	IS_RUNNING = false;
}

vector<string> get_all_files_names_within_folder(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

void AgainMenu(bool &rematch) {
	Console::DrawBorder(70, 25, 3, 40, ColorCode_DarkWhite);
	Console::gotoXY(72, 26);
	printf("Play again?");
	Console::TextColor(ColorCode_Green);
	Console::gotoXY(90, 26);
	printf("Yes");
	Console::TextColor(ColorCode_DarkWhite);
	Console::gotoXY(105, 26);
	printf("No");

	int choose = 1;

	while (1) {
		char c = toupper(_getch());
		if (c == 'A') {
			Console::TextColor(ColorCode_Green);
			Console::gotoXY(90, 26);
			printf("Yes");
			Console::TextColor(ColorCode_DarkWhite);
			Console::gotoXY(105, 26);
			printf("No");
			choose = 1;
		}
		else if (c == 'D') {
			Console::TextColor(ColorCode_DarkWhite);
			Console::gotoXY(90, 26);
			printf("Yes");
			Console::TextColor(ColorCode_Green);
			Console::gotoXY(105, 26);
			printf("No");
			choose = 2;
		}
		else if (c == '\r')
			break;
		else if (c == Special_Key || c == Special_Key_2) {
			c = _getch();
			if (c == KEY_LEFT) {
				Console::TextColor(ColorCode_Green);
				Console::gotoXY(90, 26);
				printf("Yes");
				Console::TextColor(ColorCode_DarkWhite);
				Console::gotoXY(105, 26);
				printf("No");
				choose = 1;
			}
			else if (c == KEY_RIGHT) {
				Console::TextColor(ColorCode_DarkWhite);
				Console::gotoXY(90, 26);
				printf("Yes");
				Console::TextColor(ColorCode_Green);
				Console::gotoXY(105, 26);
				printf("No");
				choose = 2;
			}
		}
	}

	if (choose == 1) {
		rematch = true;
	}
	else if (choose == 2) {	
		rematch = false;
	}
	return;
}

void NextLevelMenu(bool &rematch) {
	Console::DrawBorder(70, 25, 3, 40, ColorCode_DarkWhite);
	Console::gotoXY(72, 26);
	printf("Next level?");
	Console::TextColor(ColorCode_Green);
	Console::gotoXY(90, 26);
	printf("Yes");
	Console::TextColor(ColorCode_DarkWhite);
	Console::gotoXY(105, 26);
	printf("No");

	int choose = 1;

	while (1) {
		char c = toupper(_getch());
		if (c == 'A') {
			Console::TextColor(ColorCode_Green);
			Console::gotoXY(90, 26);
			printf("Yes");
			Console::TextColor(ColorCode_DarkWhite);
			Console::gotoXY(105, 26);
			printf("No");
			choose = 1;
		}
		else if (c == 'D') {
			Console::TextColor(ColorCode_DarkWhite);
			Console::gotoXY(90, 26);
			printf("Yes");
			Console::TextColor(ColorCode_Green);
			Console::gotoXY(105, 26);
			printf("No");
			choose = 2;
		}
		else if (c == '\r')
			break;

		else if (c == Special_Key || c == Special_Key_2) {
			c = _getch();
			if (c == KEY_LEFT) {
				Console::TextColor(ColorCode_Green);
				Console::gotoXY(90, 26);
				printf("Yes");
				Console::TextColor(ColorCode_DarkWhite);
				Console::gotoXY(105, 26);
				printf("No");
				choose = 1;
			}
			else if (c == KEY_RIGHT) {
				Console::TextColor(ColorCode_DarkWhite);
				Console::gotoXY(90, 26);
				printf("Yes");
				Console::TextColor(ColorCode_Green);
				Console::gotoXY(105, 26);
				printf("No");
				choose = 2;
			}
		}
	}

	if (choose == 1) {
		rematch = true;
	}
	else if (choose == 2) {
		rematch = false;
	}
	return;
}

void setSleepTime() {
	switch (curLevel) {
	case 1:
		sleepTime = LEVEL_1_SLEEP_TIME;
		break;
	case 2:
		sleepTime = LEVEL_2_SLEEP_TIME;
		break;
	case 3:
		sleepTime = LEVEL_3_SLEEP_TIME;
		break;
	case 4:
		sleepTime = LEVEL_4_SLEEP_TIME;
		break;
	case 5:
		sleepTime = LEVEL_5_SLEEP_TIME;
		break;
	case 6:
		sleepTime = LEVEL_6_SLEEP_TIME;
		break;
	case 7:
		sleepTime = LEVEL_7_SLEEP_TIME;
		break;
	case 8:
		sleepTime = LEVEL_8_SLEEP_TIME;
		break;
	case 9:
		sleepTime = LEVEL_9_SLEEP_TIME;
		break;
	case 10:
		sleepTime = LEVEL_10_SLEEP_TIME;
		break;
	}
}

void SubThread() {
	game->setTrafficLightCount(0);
	
	while (IS_RUNNING) {
		if (game->isStarted()) {
			game->updatePosPeople(MOVING);
			MOVING = ' ';

			if (game->getTrafficLight() == GREEN_LIGHT)
				game->updatePosVehicle();

			game->updatePosAnimal();

			if (game->isImpact()) {
				game->getPeople().draw();
				game->setStarted(false);
				game->drawNotification(false);

				if (SOUND_ON) {
					mciSendString(_T("stop mp3"), NULL, 0, 0);
					mciSendString(_T("close mp3"), NULL, 0, 0);
					mciSendString(_T("open Sound\\mario_gameover.mp3 alias mp3"), NULL, 0, 0);
					mciSendString(_T("play mp3"), NULL, 0, 0);
				}

				gameState = GAME_LOSE; 
				game->setTrafficLightCount(0);
				game->setTrafficLight(GREEN_LIGHT);
			}

			if (game->isWin()) {
				game->drawNotification(true);
				gameState = GAME_WIN;

				if (SOUND_ON) {
					mciSendString(_T("stop mp3"), NULL, 0, 0);
					mciSendString(_T("close mp3"), NULL, 0, 0);
					mciSendString(_T("open Sound\\mario_victory.mp3 alias mp3"), NULL, 0, 0);
					mciSendString(_T("play mp3"), NULL, 0, 0);
				}

				game->setStarted(false);
				game->setTrafficLightCount(0);
				game->setTrafficLight(GREEN_LIGHT);
			}

			game->setTrafficLightCount(game->getTrafficLightCount() + 1);

			if (game->getTrafficLightCount() == 3000 / sleepTime) {
				game->setTrafficLight(RED_LIGHT);
				game->drawTrafficLight();
			}

			if (game->getTrafficLightCount() == 4500 / sleepTime) {
				game->setTrafficLightCount(0);
				game->setTrafficLight(GREEN_LIGHT);
				game->drawTrafficLight();
			}
		}
		Sleep(sleepTime);
	}
	if (SOUND_ON) {
		mciSendString(_T("stop mp3"), NULL, 0, 0);
		mciSendString(_T("close mp3"), NULL, 0, 0);
	}
}

void getKey(char &tmp) {
	if (tmp == 'W')
		MOVING = 'W';
	else if (tmp == 'S')
		MOVING = 'S';
	else if (tmp == 'A')
		MOVING = 'A';
	else if (tmp == 'D')
		MOVING = 'D';
	else if (tmp == 'L')
		MOVING = 'L';
}

void drawMainMenu() {
	game->drawName();
	Console::DrawTable(35, 13, 17, 55, 240);
	Console::DrawBorder(41, 14, 3, 43, 252);
	Console::TextColor(240);
	Console::DrawBorder(41, 18, 3, 43, 240);
	Console::DrawBorder(41, 22, 3, 43, 240);
	Console::DrawBorder(41, 26, 3, 43, 240);

	Console::TextColor(252);
	Console::gotoXY(56, START_GAME_POS);
	printf("1. NEW GAME");
	Console::TextColor(240);
	Console::gotoXY(56, LOAD_GAME_POS);
	printf("2. LOAD GAME");
	Console::gotoXY(56, SETTING_GAME_POS);
	printf("3. SETTING");
	Console::gotoXY(56, EXIT_GAME_POS);
	printf("4. EXIT");
}

void drawMenuChoose(int menuPos, int color) {
	if (menuPos == START_GAME_POS) {
		menuPos = EXIT_GAME_POS;
		Console::DrawBorder(41, 14, 3, 43, color);
		Console::TextColor(color);
		Console::gotoXY(56, START_GAME_POS);
		printf("1. NEW GAME");
	}
	else if (menuPos == LOAD_GAME_POS) {
		Console::DrawBorder(41, 18, 3, 43, color);
		Console::TextColor(color);
		Console::gotoXY(56, LOAD_GAME_POS);
		printf("2. LOAD GAME");
	}
	else if (menuPos == SETTING_GAME_POS) {
		Console::DrawBorder(41, 22, 3, 43, color);
		Console::TextColor(color);
		Console::gotoXY(56, SETTING_GAME_POS);
		printf("3. SETTING");
	}
	else {
		Console::DrawBorder(41, 26, 3, 43, color);
		Console::TextColor(color);
		Console::gotoXY(56, EXIT_GAME_POS);
		printf("4. EXIT");
	}
}

void runMainMenu(int &menuPos) {
	while (1) {
		char key = _getch();
		if (key == Special_Key || key == Special_Key_2) {
			key = _getch();

			drawMenuChoose(menuPos, 240);

			if (key == KEY_UP) {
				if (menuPos == START_GAME_POS)
					menuPos = EXIT_GAME_POS;
				else
					menuPos -= 4;
			}
			else if (key == KEY_DOWN) {
				if (menuPos == EXIT_GAME_POS)
					menuPos = START_GAME_POS;
				else
					menuPos += 4;
			}

			drawMenuChoose(menuPos, 252);
		}
		else if (key == '\r') {
			break;
		}
		else if (key == 'w' || key == 'W') {
			drawMenuChoose(menuPos, 240);
			if (menuPos == START_GAME_POS)
				menuPos = EXIT_GAME_POS;
			else
				menuPos -= 4;
			drawMenuChoose(menuPos, 252);
		}
		else if (key == 's' || key == 'S') {
			drawMenuChoose(menuPos, 240);
			if (menuPos == EXIT_GAME_POS)
				menuPos = START_GAME_POS;
			else
				menuPos += 4;
			drawMenuChoose(menuPos, 252);
		}
	}
}

void saveGameMenu() {
	game->pauseGame();
	Sleep(100);		//Doi den khi game pause xong

	Console::DrawTable(30, 10, 10, 55, 224);
	Console::gotoXY(50, 11);
	Console::TextColor(228);
	printf("SAVE GAME");
	Console::gotoXY(32, 13);
	Console::TextColor(224);
	printf("You want to save game? ");
	bool save = true;

	Console::TextColor(228);
	Console::gotoXY(60, 13);
	printf("Yes");
	Console::TextColor(224);
	Console::gotoXY(75, 13);
	printf("No");

	while (1) {
		char c = toupper(_getch());
		if (c == 'A') {
			Console::TextColor(228);
			Console::gotoXY(60, 13);
			printf("Yes");
			Console::TextColor(224);
			Console::gotoXY(75, 13);
			printf("No");
			save = true;
		}
		else if (c == 'D') {
			Console::TextColor(224);
			Console::gotoXY(60, 13);
			printf("Yes");
			Console::TextColor(228);
			Console::gotoXY(75, 13);
			printf("No");
			save = false;
		}
		else if (c == '\r')
			break;
	}

	if (save) {
		string saveName;
		ofstream out;

		Console::gotoXY(34, 15);
		printf("File name: ");
		getline(cin, saveName);
		saveName = "Save\\" + saveName + ".bin";
		out.open(saveName, ios::out | ios::binary);

		if (out.is_open()) {
			game->saveGame(out, curLevel, game->getTrafficLightCount());
			Console::gotoXY(34, 16);
			Console::TextColor(228);
			printf("> Save succeed!");
			Console::TextColor(224);
			cin.ignore();

			Console::TextColor(ColorCode_DarkWhite);
			game->startGame(curLevel);
			return;
		}
		else {
			Console::gotoXY(34, 16);
			printf("Save failed!");

			Console::TextColor(ColorCode_DarkWhite);
			game->startGame(curLevel);
			return;
		}
		out.close();
	}
	else {
		Console::TextColor(ColorCode_DarkWhite);
		game->startGame(curLevel);
	}
}
								
void drawSettingChoose(int choose) {
	if (choose == 1)
		Console::DrawBorder(39, 17, 3, 47, 244);
	else
		Console::DrawBorder(39, 17, 3, 47, 240);
	Console::gotoXY(50, 18);
	if (choose == 1)
		Console::TextColor(244);
	else
		Console::TextColor(240);
	printf("Sound: ");
	Console::gotoXY(68, 18);
	if (SOUND_ON)
		printf("ON");
	else
		printf("OFF");

	if (choose == 2)
		Console::DrawBorder(39, 21, 3, 47, 244);
	else
		Console::DrawBorder(39, 21, 3, 47, 240);
	Console::gotoXY(50, 22);
	if (choose == 2)
		Console::TextColor(244);
	else
		Console::TextColor(240);
	printf("Level: ");
	Console::gotoXY(68, 22);
	printf("%2d", curLevel);

	if (choose == 3)
		Console::DrawBorder(39, 25, 3, 47, 244);
	else
		Console::DrawBorder(39, 25, 3, 47, 240);
	Console::gotoXY(60, 26);
	if (choose == 3)
		Console::TextColor(244);
	else
		Console::TextColor(240);
	printf("Exit");

	Console::TextColor(ColorCode_DarkWhite);
}

void settingMenu() {
	game->drawName();
	Console::DrawTable(35, 13, 17, 55, 240);
	Console::TextColor(244);
	Console::gotoXY(58, 15);
	printf("SETTING");
	Console::TextColor(240);

	int choose = 1;

	drawSettingChoose(choose);

	while (1) {
		char c = toupper(_getch());
		if (c == Special_Key || c == Special_Key_2) {
			c = _getch();
			if (c == KEY_UP) {
				if (choose == 1)
					continue;
				else
					choose -= 1;
				drawSettingChoose(choose);
			}
			else if (c == KEY_DOWN) {
				if (choose == 3)
					continue;
				else
					choose += 1;
				drawSettingChoose(choose);
			}
		}

		else if (c == 'W') {
			if (choose == 1)
				continue;
			else
				choose -= 1;
			drawSettingChoose(choose);
		}

		else if (c == 'S') {
			if (choose == 3)
				continue;
			else
				choose += 1;
			drawSettingChoose(choose);
		}

		else if (c == '\r') {
			if (choose == 3)
				return;
			else if (choose == 1) {
				Console::TextColor(242);
				Console::gotoXY(68, 18);
				if (SOUND_ON)
					printf("ON ");
				else
					printf("OFF");
				while (1) {
					char k = toupper(_getch());
					if (k == Special_Key || k == Special_Key_2) {
						k = _getch();
						if (k == KEY_UP || k == KEY_DOWN) {
							Console::gotoXY(68, 18);
							if (SOUND_ON) {
								SOUND_ON = false;
								printf("OFF");
							}
							else {
								SOUND_ON = true;
								printf("ON ");
							}
						}
					}

					else if (k == 'W' || k == 'S') {
						Console::gotoXY(68, 18);
						if (SOUND_ON) {
							SOUND_ON = false;
							printf("OFF");
						}
						else {
							SOUND_ON = true;
							printf("ON ");
						}
					}

					else if (k == '\r') {
						Console::TextColor(244);
						Console::gotoXY(68, 18);
						if (SOUND_ON)
							printf("ON ");
						else
							printf("OFF");
						break;
					}
				}
			}
			else if (choose == 2) {
				Console::TextColor(242);
				Console::gotoXY(68, 22);
				printf("%2d", curLevel);
				while (1) {
					char k = toupper(_getch());
					if (k == Special_Key || k == Special_Key_2) {
						k = _getch();
						if (k == KEY_DOWN) {
							if (curLevel > 1)
								curLevel--;
						}
						else if (k == KEY_UP)
							if (curLevel < 10)
								curLevel++;

						Console::gotoXY(68, 22);
						printf("%2d", curLevel);
					}

					else if (k == 'S') {
						if (curLevel > 1)
							curLevel--;
						Console::gotoXY(68, 22);
						printf("%2d", curLevel);
					}

					else if (k == 'W') {
						if (curLevel < 10)
							curLevel++;
						Console::gotoXY(68, 22);
						printf("%2d", curLevel);
					}

					else if (k == '\r') {
						Console::TextColor(244);
						Console::gotoXY(68, 22);
						printf("%2d", curLevel);
						break;
					}
				}
			}
		}
	}

}

int main() {
	Console::FixConsoleWindow();
	Console::ResizeConsoleWindow(910, 550);
	Console::HideConsolePointer();
	Console::TextColor(ColorCode_Cyan);

	Console::gotoXY(57, 13);
	printf("Loading...");

	Console::gotoXY(35, 15);
	for (int i = 0; i < 50; i++) {
		printf("%c", 219);
		Sleep(5);
	}

	system("cls");

	while (gameState != GAME_EXIT) {
		system("cls");

		if (SOUND_ON) {
			err = mciSendString(_T("open Sound\\Pubg_theme.mp3 alias mp3"), NULL, 0, 0);
			mciSendString(_T("play mp3 repeat"), NULL, 0, 0);
		}

		drawMainMenu();
		int menuPos = START_GAME_POS;
		runMainMenu(menuPos);

		setSleepTime();

		if (menuPos == START_GAME_POS) {
			//NEW GAME AREA////////////////////////////////////////////////////

			game->startGame(curLevel);

			if (SOUND_ON) {
				mciSendString(_T("stop mp3"), NULL, 0, 0);
				mciSendString(_T("close mp3"), NULL, 0, 0);
				mciSendString(_T("open Sound\\Netherplace.mp3 alias mp3"), NULL, 0, 0);
				mciSendString(_T("play mp3 repeat"), NULL, 0, 0);
			}

			IS_RUNNING = true;

			thread t1(SubThread);
			while (1) {
				char tmp = _getch();
				tmp = toupper(tmp);
				getKey(tmp);

				if (gameState == GAME_LOSE) {
					bool rematch;

					AgainMenu(rematch);
					if (!rematch) {
						system("cls");
						game->resetGame();
						game->startGame(curLevel);
						gameState = GAME_RUNNING;
						IS_RUNNING = false;
						break;
					}
					else {
						system("cls");
						curLevel = 1;
						setSleepTime();
						game->resetGame();
						game->startGame(curLevel);
						gameState = GAME_RUNNING;
						IS_RUNNING = true;
					}
				}
				else if (gameState == GAME_WIN) {
					bool nextLevel = false;
					NextLevelMenu(nextLevel); {
						if (!nextLevel) {
							system("cls");
							game->resetGame();
							game->startGame(curLevel);
							gameState = GAME_RUNNING;
							IS_RUNNING = false;
							break;
						}
						else {
							system("cls");
							curLevel++;
							setSleepTime();
							game->resetGame();
							game->startGame(curLevel);
							gameState = GAME_RUNNING;
							IS_RUNNING = true;
						}
					}
				}

				if (tmp == 27) {
					exitGame(&t1);
					break;
				}
				else if (tmp == 'L') {
					saveGameMenu();
					game->remuseGame();
				}
				else if (tmp == 'P')
					game->pauseGame();
				else if (tmp == 'R')
					game->remuseGame();
			}
			t1.join();

			if (SOUND_ON) {
				mciSendString(_T("stop mp3"), NULL, 0, 0);
				mciSendString(_T("close mp3"), NULL, 0, 0);
			}
			//////////////////////////////////////////////////////////////////////
		}
		else if (menuPos == EXIT_GAME_POS) {
			gameState = GAME_EXIT;
		}
		else if (menuPos == LOAD_GAME_POS) {
			//LOAD GAME AREA//////////////////////////////////////////////////////
			game->drawName();
			Console::DrawTable(35, 13, 17, 55, 240);
			Console::TextColor(240);
			Console::gotoXY(57, 15);
			Console::TextColor(244);
			printf("LOAD GAME");
			Console::TextColor(240);
			Console::gotoXY(40, 17);
			printf("You want to load game? ");

			Console::gotoXY(70, 17);
			Console::TextColor(242);
			printf("Yes");
			Console::gotoXY(80, 17);
			Console::TextColor(240);
			printf("No");

			bool load = true;

			while (1) {
				char c = toupper(_getch());
				if (c == 'A') {
					Console::gotoXY(70, 17);
					Console::TextColor(242);
					printf("Yes");
					Console::gotoXY(80, 17);
					Console::TextColor(240);
					printf("No");
					load = true;
				}
				else if (c == 'D') {
					Console::gotoXY(70, 17);
					Console::TextColor(240);
					printf("Yes");
					Console::gotoXY(80, 17);
					Console::TextColor(242);
					printf("No");
					load = false;
				}
				else if (c == '\r')
					break;
				else if (c == Special_Key || c == Special_Key_2) {
					c = _getch();
					if (c == KEY_LEFT) {
						Console::gotoXY(70, 17);
						Console::TextColor(242);
						printf("Yes");
						Console::gotoXY(80, 17);
						Console::TextColor(240);
						printf("No");
						load = true;
					}
					else if (c == KEY_RIGHT) {
						Console::gotoXY(70, 17);
						Console::TextColor(240);
						printf("Yes");
						Console::gotoXY(80, 17);
						Console::TextColor(242);
						printf("No");
						load = false;
					}
				}
			}

			if (load) {
				string name;
				ifstream in;
				Console::TextColor(240);
				int n = -1;

				vector<string> files = get_all_files_names_within_folder("Save\\");

				for (int i = 0; i < files.size(); i++) {
					Console::gotoXY(40, 19 + i);
					cout << i + 1 << ". " << files[i];
				}

				int choose_y = Console::whereY() + 2;
				while (n <= 0 || n > files.size()) {
					Console::gotoXY(40, choose_y + 2);
					printf("                              ");
					Console::gotoXY(40, choose_y);
					printf("Choose: ");
					Console::gotoXY(49, choose_y);
					printf("  ");
					Console::gotoXY(49, choose_y);
					scanf_s("%d", &n);
					if (n <= 0 || n > files.size()) {
						Console::gotoXY(40, choose_y + 2);
						printf("Error! Please type again...");
						cin.ignore();
						cin.ignore();
					}
				}
				name = "Save\\" + files[n - 1];

				in.open(name, ios::in | ios::binary);

				Console::TextColor(ColorCode_DarkWhite);

				if (in.is_open()) {
					int count;
					game->loadGame(in, curLevel, count);
					game->setTrafficLightCount(count);

					game->startGame(curLevel);

					setSleepTime();

					IS_RUNNING = true;

					if (SOUND_ON) {
						mciSendString(_T("stop mp3"), NULL, 0, 0);
						mciSendString(_T("close mp3"), NULL, 0, 0);
						mciSendString(_T("open Sound\\Netherplace.mp3 alias mp3"), NULL, 0, 0);
						mciSendString(_T("play mp3 repeat"), NULL, 0, 0);
					}

					//PLAY GAME////////////////////

					thread t1(SubThread);

					while (1) {
						char tmp = _getch();
						tmp = toupper(tmp);
						getKey(tmp);

						if (gameState == GAME_LOSE) {
							bool rematch;
							AgainMenu(rematch);
							if (!rematch) {
								system("cls");
								game->resetGame();
								game->startGame(curLevel);
								gameState = GAME_RUNNING;
								IS_RUNNING = false;
								break;
							}
							else {
								system("cls");
								curLevel = 1;
								setSleepTime();
								game->resetGame();
								game->startGame(curLevel);
								gameState = GAME_RUNNING;
								IS_RUNNING = true;
							}
						}
						else if (gameState == GAME_WIN) {
							bool nextLevel = false;
							NextLevelMenu(nextLevel); {
								if (!nextLevel) {
									system("cls");
									game->resetGame();
									game->startGame(curLevel);
									gameState = GAME_RUNNING;
									IS_RUNNING = false;
									break;
								}
								else {
									system("cls");
									curLevel++;
									setSleepTime();
									game->resetGame();
									game->startGame(curLevel);
									gameState = GAME_RUNNING;
									IS_RUNNING = true;
								}
							}
						}

						if (tmp == 27) {
							exitGame(&t1);
							break;
						}
						else if (tmp == 'L') {
							saveGameMenu();
							game->remuseGame();
						}
						else if (tmp == 'P')
							game->pauseGame();
						else if (tmp == 'R')
							game->remuseGame();
					}
					t1.join();

					mciSendString(_T("stop mp3"), NULL, 0, 0);
					mciSendString(_T("close mp3"), NULL, 0, 0);
				}
			}
			else 
				Console::TextColor(ColorCode_DarkWhite);
			////////////////////////////////////////////////////////////////
		}
		else if (menuPos == SETTING_GAME_POS) {
			settingMenu();
		}

		mciSendString(_T("stop mp3"), NULL, 0, 0);
		mciSendString(_T("close mp3"), NULL, 0, 0);

	}

	delete game;
	return 0;
}