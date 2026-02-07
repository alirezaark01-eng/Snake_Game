#include <iostream>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

bool gameOver;
int x, y;
int fruitX, fruitY;
int score;
int tailX[1000];
int tailY[1000];
int nTail;
time_t startTime;
string currentPlayerName;

double gameDelay = 200.0; 

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

extern void Draw();
extern void Input();
extern void SaveScore();
extern void ShowScoreboard();
extern void SetColor(int color);
extern void Setup();

void Logic(){
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
        }
    
    switch (dir) {
    case LEFT:  x--; break;
    case RIGHT: x++; break;
    case UP:    y--; break;
    case DOWN:  y++; break;
    default:    break;
    }
}