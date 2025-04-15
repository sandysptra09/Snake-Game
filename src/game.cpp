#include "game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

const char *fruitEmoji[] = {"¤", "ø", "×", "♦", "♣", "♠", "☼"};

void Setup(Snake *s)
{
    s->gameOver = false;
    s->dir = RIGHT;
    s->x = 10;
    s->y = 10;
    s->fruitX = 1 + rand() % 18;
    s->fruitY = 1 + rand() % 18;
    s->score = 0;

    // inisialisasi tail ngejadiin linked list kosong
    s->tail = nullptr;
    s->tailLength = 0;
}

void Draw(Snake *s, int frameCount)
{
    // Handle Console (Text Attribute)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // bersihin layar
    system("cls");

    // border atas
    for (int i = 0; i < 42; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < 22; i++)
    {
        // loop buat ngegambar baris
        for (int j = 0; j < 22; j++)
        {
            // loop buat ngegambar kolom

            // ngegambar dinding di sisi kiri dan kanan
            if (j == 0 || j == 21)
                cout << "#";

            // ngegambar kepala ular
            else if (i == s->y && j == s->x)
            {
                SetConsoleTextAttribute(hConsole, 10);
                cout << "O ";
                SetConsoleTextAttribute(hConsole, 7);
            }
            else if (i == s->fruitY && j == s->fruitX)
            {
                cout << fruitEmoji[s->score % 6] << " ";
            }
            else
            {
                bool printed = false;
                TailNode *current = s->tail;

                // traversal linked list buat ngegambar tail
                while (current != nullptr)
                {
                    if (current->x == j && current->y == i)
                    {
                        SetConsoleTextAttribute(hConsole, 2);
                        cout << "o ";
                        SetConsoleTextAttribute(hConsole, 7);
                        printed = true;
                        break;
                    }
                    current = current->next;
                }
                // kosongin kalo ga ada segmen tail di posisi itu
                if (!printed)
                {
                    cout << "  ";
                }
            }
        }
        cout << endl;
    }

    // border bawah
    for (int i = 0; i < 42; i++)
        cout << "#";
    cout << endl;

    // tampilin skor
    cout << "Score: " << s->score << endl;
    cout << endl;

    SetConsoleTextAttribute(hConsole, 12);
    cout << "Press X to Exit The Game" << endl;
    SetConsoleTextAttribute(hConsole, 7);
}
// fungsi buat nanganin input dari pemain
void Input(Snake *s)
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if (s->dir != RIGHT)
                s->dir = LEFT;
            break;
        case 'd':
            if (s->dir != LEFT)
                s->dir = RIGHT;
            break;
        case 'w':
            if (s->dir != DOWN)
                s->dir = UP;
            break;
        case 's':
            if (s->dir != UP)
                s->dir = DOWN;
            break;
        case 'x':
            s->gameOver = true;
            break;
        }
    }
}

// fungsi buat ngelola logika permainan
void Logic(Snake *s, bool &scored)
{
    scored = false;

    // simpan posisi kepala sebelum bergerak
    int prevX = s->x;
    int prevY = s->y;
    int prev2X, prev2Y;

    // update posisi kepala berdasarkan arah
    switch (s->dir)
    {
    case LEFT:
        s->x--;
        break;
    case RIGHT:
        s->x++;
        break;
    case UP:
        s->y--;
        break;
    case DOWN:
        s->y++;
        break;
    }

    if (s->x >= 21)
        s->gameOver = true;
    if (s->x < 0)
        s->gameOver = true;
    if (s->y >= 21)
        s->gameOver = true;
    if (s->y < 0)
        s->gameOver = true;

    // update posisi tail
    TailNode *current = s->tail;
    while (current != nullptr)
    {
        prev2X = current->x;
        prev2Y = current->y;
        current->x = prevX;
        current->y = prevY;
        prevX = prev2X;
        prevY = prev2Y;
        current = current->next;
    }

    // cek tabrakan dengan tail
    current = s->tail;
    while (current != nullptr)
    {
        if (current->x == s->x && current->y == s->y)
        {
            s->gameOver = true;
            break;
        }
        current = current->next;
    }

    // cek apakah kepala ular menyentuh buah
    if (s->x == s->fruitX && s->y == s->fruitY)
    {
        s->score += 10;
        s->fruitX = 1 + rand() % 18;
        s->fruitY = 1 + rand() % 18;

        // tambah segmen baru
        AddTailSegment(s, prevX, prevY);
        scored = true;
    }

    if (s->gameOver == true)
    {
        Beep(1000, 100);
    }
}