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






void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
    startTime = time(0);
    
    // Reset speed to initial slow state
    gameDelay = 200.0; 
    
    HideCursor();
}

void Draw() {
    SetCursorPosition(0, 0);

    SetColor(7); // White
    
    for (int i = 0; i < width + 2; i++)
        cout << "_";
        cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) {
                SetColor(7); 
                cout << "|";
            }

            if (i == y && j == x) {
                SetColor(10); // Green
                cout << "O";
            }

            else if (i == fruitY && j == fruitX) {
                SetColor(12); // Red
                cout << "*";
            }
            else {
                bool print = false;
                
                for (int k = 0; k < nTail; k++) {
                    
                    if (tailX[k] == j && tailY[k] == i) {
                        SetColor(10); // Green
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1) {
                SetColor(7); 
                cout << "|";
            }
        }
        
        cout << endl;
    }

    SetColor(7); 
    for (int i = 0; i < width + 2; i++)
        cout << "_";
        cout << endl;

    cout << "Score:" << score << endl;
    cout << "Time: " << (int)difftime(time(0), startTime) << "s   " << endl;
    cout << "Speed Delay: " << (int)gameDelay << "ms   " << endl; 
    cout << "Use \"W_A_S_D\" to move. X to quit." << endl;
}



enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
extern eDirection dir;

void Input() {

    if (_kbhit()) {
        char current = _getch();
        
        switch (current) {
        case 'a':
        case 'A':
            if (dir != RIGHT) dir = LEFT;
            break;
            
        case 'd':
        case 'D':
            if (dir != LEFT) dir = RIGHT;
            break;
            
        case 'w':
        case 'W':
            if (dir != DOWN) dir = UP;
            break;
            
        case 's': 
        case 'S':
            if (dir != UP) dir = DOWN;
            break;
            
        case 'x':
        case 'X':
            gameOver = true;
            break;

            
            
        }
    }
}


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

    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        Beep(1600,35);
        score += 10;

        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;

        if (nTail >= 1000)
            nTail = 999;

        gameDelay = max(50.0, gameDelay - 10.0);
    }
}

int main() {
    bool appRunning = true;

    system("cls");
    cout << "Enter your name: ";
    cin >> currentPlayerName;

    while (appRunning) {
        Setup(); 
        
        auto lastTime = std::chrono::steady_clock::now();

    
        while (!gameOver) {
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();


            Input();

    
            if (elapsedTime > gameDelay) {
                Logic();
                Draw();
                lastTime = currentTime;
            }
            Sleep(1); 
        }


        system("cls");
        Beep(300,35);
        SetColor(12); // Red
        cout << "          YOU LOST!               " << endl;
        SetColor(7); // White
        cout << "      Final Score: " << score << "      " << endl;


        SaveScore();
        ShowScoreboard();
        
        cout << "\n Press 'R' to Retry, 'X' to Quit  " << endl;


        
        bool waitingForInput = true;
        
        while (waitingForInput) {
            
            if (_kbhit()) {
                char ch = _getch();
                if (ch == 'r' || ch == 'R') {
                    system("cls"); 
                    waitingForInput = false;
            
                }
                else if (ch == 'x' || ch == 'X') {
                    waitingForInput = false;
                    appRunning = false; 
                }
            }
            Sleep(10);
        }
    }

    return 0;
}
