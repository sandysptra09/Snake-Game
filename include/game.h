#ifndef GAME_H
#define GAME_H
#include "snake.h"

void Setup(Snake* snake);

void Draw(Snake* snake, int frameCount);

void Input(Snake* snake);

void Logic(Snake* snake, bool& scored);

#endif