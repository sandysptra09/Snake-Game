#include "snake.h"
#include <cstdlib>
#include <windows.h>
using namespace std;

// nambahahin segment tail baru ke linked list
void AddTailSegment(Snake *s, int newX, int newY)
{
    // buat node baru untuk tail
    TailNode *newNode = new TailNode;
    newNode->x = newX;
    newNode->y = newY;
    newNode->next = nullptr;

    if (s->tail == nullptr)
    {
        // jika tailnya kosong, maka node baru jadi head dari linked list
        s->tail = newNode;
    }
    else
    {
        // traversal sampai node terakhir
        TailNode *current = s->tail;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
        Beep(1000, 100);
    }
    s->tailLength++;
}

// ngehapus semua node di linked list tail
void FreeTail(Snake *s)
{
    TailNode *current = s->tail;
    while (current != nullptr)
    {
        TailNode *next = current->next;
        delete current;
        current = next;
    }
    s->tail = nullptr;
    s->tailLength = 0;
}