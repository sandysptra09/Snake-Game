#ifndef SNAKE_H
#define SNAKE_H

// nentuin arah pergerakan
enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// struct untuk menyimpan posisi tail
struct TailNode
{
    int x, y;
    TailNode *next;
};

// struct buat snake menggunakan linked list
struct Snake
{
    int x, y;
    int fruitX, fruitY;
    int score;
    TailNode *tail;
    int tailLength;
    eDirection dir;
    bool gameOver;
};

// prototype fungsi-fungsi pengelolaan tail (linked list)
void AddTailSegment(Snake *s, int newX, int newY);
void FreeTail(Snake *s);

#endif