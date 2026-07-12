#include "../../dependencies/raylib/include/raylib.h"

#include <initializer_list>
#include <vector>

std::vector<Sound> multipleSoundLoad(std::initializer_list<const char*> chemins)
{
    std::vector<Sound> sounds;

    for (const char* path : chemins)
    {
        sounds.push_back(LoadSound(path));
    }

    return sounds;
}