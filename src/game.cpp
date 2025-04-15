#include "game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

const char *fruitEmoji[] = {"🍎", "🍌", "🍇", "🍓", "🍉", "🍍"};

void MoveFruit(Snake *s, int frameCount)
{
    // Gerakkan buah setiap beberapa frame
    if (frameCount % 10 == 0)
    {                                // Setiap 10 frame (bisa diubah)
        s->fruitX = 1 + rand() % 18; // Posisi X buah
        s->fruitY = 1 + rand() % 18; // Posisi Y buah
    }
}

void Setup(Snake *s)
{
    s->gameOver = false;
    s->dir = RIGHT;
    s->x = 10;
    s->y = 10;
    s->fruitX = 1 + rand() % 18;
    s->fruitY = 1 + rand() % 18;
    s->score = 0;
    s->tail = nullptr; // Inisialisasi tail sebagai linked list kosong
    s->tailLength = 0;
}

void Draw(Snake *s, int frameCount)
{
    // Handle Console (Text Attribute)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Clear layar
    system("cls");

    // Border Atas
    for (int i = 0; i < 42; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < 22; i++)
    { // Loop untuk menggambar baris
        for (int j = 0; j < 22; j++)
        {                          // Loop untuk menggambar kolom
            if (j == 0 || j == 21) // Gambar dinding di sisi kiri dan kanan
                cout << "#";
            else if (i == s->y && j == s->x) // Gambar kepala ular
                cout << "O ";
            else if (i == s->fruitY && j == s->fruitX)
                cout << fruitEmoji[s->score % 6] << " ";
            else
            {
                bool printed = false;
                TailNode *current = s->tail;
                // Traversal linked list untuk menggambar tail
                while (current != nullptr)
                {
                    if (current->x == j && current->y == i)
                    {
                        cout << "o ";
                        printed = true;
                        break;
                    }
                    current = current->next;
                }
                if (!printed)
                    cout << "  "; // Kosongkan jika tidak ada segmen tail di posisi itu
            }
        }
        cout << endl;
    }

    // Border Bawah
    for (int i = 0; i < 42; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << s->score << endl; // Tampilkan skor
    cout << endl;
    SetConsoleTextAttribute(hConsole, 12);
    cout << "Press X to Exit The Game" << endl;
    SetConsoleTextAttribute(hConsole, 7);
}
// Fungsi untuk menangani input dari pemain
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

// Fungsi untuk mengelola logika permainan
void Logic(Snake *s, bool &scored)
{
    scored = false;

    // Simpan posisi kepala sebelum bergerak
    int prevX = s->x;
    int prevY = s->y;
    int prev2X, prev2Y;
    // Update posisi kepala berdasarkan arah
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

    // Update posisi tail
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

    // Cek tabrakan dengan tail
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

    // Cek apakah kepala ular menyentuh buah
    if (s->x == s->fruitX && s->y == s->fruitY)
    {
        s->score += 10;
        s->fruitX = 1 + rand() % 18;
        s->fruitY = 1 + rand() % 18;
        AddTailSegment(s, prevX, prevY); // Tambah segmen baru
        scored = true;
    }
}