#include "game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

// fungsi Setup untuk inisialisasi permainan
void Setup(Snake *s)
{
    s->gameOver = false;

    // mulai bergerak ke kanan
    s->dir = RIGHT;

    // posisi kepala ular
    s->x = 10;
    s->y = 10;

    // posisi buah
    s->fruitX = rand() % 20;
    s->fruitY = rand() % 20;

    // skor awal
    s->score = 0;

    // tail kosong
    s->tail = nullptr;

    // tidak ada tail
    s->nTail = 0;
}

void Draw(Snake *s, int frameCount)
{

    // Clear layar
    system("cls");

    for (int i = 0; i < 20; i++)
    { // Loop untuk menggambar baris
        for (int j = 0; j < 20; j++)
        {                          // Loop untuk menggambar kolom
            if (j == 0 || j == 19) // Gambar dinding di sisi kiri dan kanan
                cout << "#";
            else if (i == s->y && j == s->x) // Gambar kepala ular
                cout << "O ";
            else if (i == s->fruitY && j == s->fruitX) // Gambar buah
                cout << "F ";
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
            if (j == 19)
                cout << "#"; // Gambar dinding bawah
        }
        cout << endl;
    }

    cout << "Score: " << s->score << endl; // Tampilkan skor
}
// Fungsi untuk menangani input dari pemain
void Input(Snake *s)
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            s->dir = LEFT;
            break;
        case 'd':
            s->dir = RIGHT;
            break;
        case 'w':
            s->dir = UP;
            break;
        case 's':
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

    if (s->x >= 20)
        s->x = 0;
    if (s->x < 0)
        s->x = 19;
    if (s->y >= 20)
        s->y = 0;
    if (s->y < 0)
        s->y = 19;

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
        s->fruitX = rand() % 20;
        s->fruitY = rand() % 20;
        AddTailSegment(s, prevX, prevY); // Tambah segmen baru
        scored = true;
    }
}