#include <iostream>
#include "game.h"
#include "utils.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <thread>
using namespace std;

void TypeOut(const std::string& text, int delayMs = 30) {
    for (char c : text) {
        cout << c << flush;
        Sleep(delayMs);
    }
    cout << endl;
}

void ShowGameOverScreen(int score, int highscore, bool isHighscore) {
    system("cls");
    string border = "==============================";

    for (int i = 0; i < 3; i++) {
        system("cls");
        cout << endl << border << endl;
        cout << "  ❌  G A M E   O V E R  ❌" << endl;
        cout << border << endl;
        

        system("cls");
        cout << endl << border << endl;
        cout << "                              " << endl;
        cout << border << endl;
        
    }

    system("cls");
    cout << endl << border << endl;
    cout << "  ❌  G A M E   O V E R  ❌" << endl;
    cout << border << endl;

    if (isHighscore) {
        TypeOut("🎉 New Highscore: " + to_string(score) + " 🎉", 40);
    } else {
        TypeOut("💀 Your Score   : " + to_string(score), 40);
        TypeOut("🏆 Highscore    : " + to_string(highscore), 40);
    }

    cout << border << endl;
}

void ShowMainMenu() {
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    const string title1 = "  ___ _  _   _   _  _____    ___   _   __  __ ___ ";
    const string title2 = " / __| \\| | /_\\ | |/ / __|  / __| /_\\ |  \\/  | __|";
    const string title3 = " \\__ \\ .` |/ _ \\| ' <| _|  | (_ |/ _ \\| |\\/| | _| ";
    const string title4 = " |___/_|\\_/_/ \\_\\_|\\_\\___|  \\___/_/ \\_\\_|  |_|___|";

    const int paddingLeft = 10;
    const int titleWidth = title1.length();
    const int promptWidth = string("Press any key to play...").length();
    const int centerOffset = paddingLeft + (titleWidth - promptWidth) / 2;

    bool show = true;
    int blinkCounter = 0;
    while (!_kbhit()) {
        system("cls");
        SetConsoleTextAttribute(hConsole, 11);
        cout << string(paddingLeft, ' ') << title1 << endl;
        cout << string(paddingLeft, ' ') << title2 << endl;
        cout << string(paddingLeft, ' ') << title3 << endl;
        cout << string(paddingLeft, ' ') << title4 << endl;
        SetConsoleTextAttribute(hConsole, 7);
        cout << endl;

        if (blinkCounter % 10 < 5) {
            SetConsoleTextAttribute(hConsole, 14);
            cout << string(centerOffset, ' ') << "Press any key to play..." << endl;
            SetConsoleTextAttribute(hConsole, 7);
        } else {
            cout << endl;
        }

        
        blinkCounter++;
    }
    _getch();
}

int main(){
    ShowMainMenu();

    Snake snake;
    Setup(&snake);
    int highscore = LoadHighScore("assets/highscore.txt");

    int frameCount = 0;
    bool scored = false;

    while (!snake.gameOver) {
        Draw(&snake, frameCount);
        Input(&snake);
        Logic(&snake, scored);
        Sleep(100);
        frameCount++;
    }

    FreeTail(&snake);
    
    bool isHigh = false;
    if (snake.score > highscore) {
        SaveHighScore("assets/highscore.txt", snake.score);
        isHigh = true;
    }
    
    ShowGameOverScreen(snake.score, highscore, isHigh);
    cout << "Game Over!" << endl;
    system("pause");
    return 0;
}