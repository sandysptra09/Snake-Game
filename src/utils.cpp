#include "utils.h"
#include <fstream>
using namespace std;

int LoadHighScore(const string &filename)
{
    ifstream file(filename);
    int score = 0;
    if (file.is_open())
    {
        file >> score;
        file.close();
    }
    return score;
}

void SaveHighScore(const string &filename, int score)
{
    ofstream file(filename);
    if (file.is_open())
    {
        file << score;
        file.close();
    }
}