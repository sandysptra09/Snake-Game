#ifndef SNAKE_H
#define SNAKE_H

enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct SnakeSegment
{
    int x;
    int y;
};