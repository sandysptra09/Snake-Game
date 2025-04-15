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