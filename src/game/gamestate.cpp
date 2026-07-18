#include "gamestate.h"

#include <iostream>

#include "raylib.h"

int current_night = 1;
bool intro = false;
char* save;

void loadSave()
{
    save = LoadFileText("../saves/save.txt");
    std::cout << save;
}