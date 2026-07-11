#pragma once

int current_night;
bool intro;

char* save;

void loadSave()
{
    save = LoadFileText("../saves/save.txt");
    std::cout << save;
}