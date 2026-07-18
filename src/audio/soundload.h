#pragma once
#include <initializer_list>
#include <vector>

#include "raylib.h"

std::vector<Sound> multipleSoundLoad(std::initializer_list<const char*> chemins);