#ifndef GAME_H
#define GAME_H
#include "snake.h"

// fungsi Setup buat inisialisasi permainan
void Setup(Snake *snake);

// fungsi Draw buat ngegambar permainan
void Draw(Snake *snake, int frameCount);

// fungsi Input buat ngecek input dari user
void Input(Snake *snake);

// fungsi Logic buat ngelakuin logika permainan
void Logic(Snake *snake, bool &scored);

#endif
