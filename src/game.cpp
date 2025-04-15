#include "game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

// Fungsi Setup untuk inisialisasi permainan
void Setup(Snake* s) {
    s->gameOver = false;
    s->dir = RIGHT;        // Mulai bergerak ke kanan
    s->x = 10;             // Posisi kepala ular
    s->y = 10;
    s->fruitX = rand() % 20;  // Posisi buah
    s->fruitY = rand() % 20;
    s->score = 0;              // Skor awal
    s->tail = nullptr;         // Tail kosong
    s->nTail = 0;              // Tidak ada tail
}