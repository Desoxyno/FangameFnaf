#pragma once

#include "../../dependencies/raylib/include/raylib.h"

#include <string>

class GameObject
{
  public:
    std::string name;
    Model model;
    ModelAnimation* animations = nullptr;
    int animationCount = 0;
    Vector3 position = {0.0f, 0.0f, 0.0f};
    Vector3 rotation = {0.0f, 0.0f, 0.0f};
    Vector3 scale = {1.0f, 1.0f, 1.0f};
};