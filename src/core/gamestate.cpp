#include "gamestate.h"

#include "../../dependencies/raylib/include/raylib.h"
#include "iostream"

int current_night = 1;
bool intro = false;
char* save;

void loadSave()
{
    save = LoadFileText("../saves/save.txt");
    std::cout << save;
}