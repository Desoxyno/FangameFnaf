#pragma once
#include "../../dependencies/raylib/include/raylib.h"

#include <initializer_list>
#include <vector>

std::vector<Sound> multipleSoundLoad(std::initializer_list<const char*> chemins);