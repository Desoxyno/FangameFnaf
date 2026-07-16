#pragma once

#include "../../dependencies/raylib/include/raylib.h"

class DebugMode
{
  public:
    Ray ray = {0};
    RayCollision collision = {0};
    Camera camera;
    void ActivateDebugMode();
    void Update();
    void Draw();
};
