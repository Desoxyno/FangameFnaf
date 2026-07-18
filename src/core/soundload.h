#pragma once
#include <initializer_list>
#include <vector>

#include "../../dependencies/raylib/include/raylib.h"

std::vector<Sound> multipleSoundLoad(std::initializer_list<const char*> chemins);