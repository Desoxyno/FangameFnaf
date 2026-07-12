#pragma once

#include "../../dependencies/raylib/include/raylib.h"

class GameObject
{
  public:
    Model model;
    Vector3 position = {0.0f, 0.0f, 0.0f};
};