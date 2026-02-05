#include <iostream>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct Player {
    string name;
    int score;
};

const int width = 20;
const int height = 20;

extern bool gameOver;
extern int x, y;
extern int fruitX, fruitY;
extern int score;
extern int tailX[1000];
extern int tailY[1000];
extern int nTail;
extern time_t startTime;
extern string currentPlayerName;
extern double gameDelay;



// Sets the text color in the console (7=White, 10=Green, 12=Red, 14=Yellow)
void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void SetCursorPosition(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void HideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}