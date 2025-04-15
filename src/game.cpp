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

void Draw(Snake* s, int frameCount) {
    system("cls");  // Clear layar

    for (int i = 0; i < 20; i++) { // Loop untuk menggambar baris
        for (int j = 0; j < 20; j++) { // Loop untuk menggambar kolom
            if (j == 0 || j == 19) // Gambar dinding di sisi kiri dan kanan
                cout << "#";
            else if (i == s->y && j == s->x) // Gambar kepala ular
                cout << "O ";
            else if (i == s->fruitY && j == s->fruitX) // Gambar buah
                cout << "F ";
            else {
                bool printed = false;
                TailNode* current = s->tail;
                // Traversal linked list untuk menggambar tail
                while (current != nullptr) {
                    if (current->x == j && current->y == i) {
                        cout << "o ";
                        printed = true;
                        break;
                    }
                    current = current->next;
                }
                if (!printed)
                    cout << "  "; // Kosongkan jika tidak ada segmen tail di posisi itu
            }
            if (j == 19) cout << "#"; // Gambar dinding bawah
        }
        cout << endl;
    }

    cout << "Score: " << s->score << endl; // Tampilkan skor
}