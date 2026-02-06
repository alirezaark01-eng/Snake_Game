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



void SaveScore() {
    ofstream file("snake_scores.txt", ios::app);
    if (file.is_open()) {
        file << currentPlayerName << " " << score << endl;
        file.close();
    }
}

void ShowScoreboard() {
    ifstream file("snake_scores.txt");
    Player players[100]; // Array to hold scores loaded from file
    int count = 0;

    if (file.is_open()) {
        while (count < 100 && file >> players[count].name >> players[count].score) {
            count++;
        }
        file.close();
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }

    SetColor(14); // Yellow
    cout << "\n======= HIGH SCORES =======\n";
    if (count == 0) {
        cout << "No scores saved yet.\n";
    }
    for (int i = 0; i < count && i < 10; i++) { 
        cout << (i + 1) << ". " << players[i].name << " - " << players[i].score << endl;
    }
    cout << "===========================\n";
    SetColor(7); // Reset to White
}