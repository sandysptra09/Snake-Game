#ifndef UTILS_H
#define UTILS_H
#include <string>

int LoadHighScore(const std::string &filename);
void SaveHighScore(const std::string &filename, int score);

#endif
