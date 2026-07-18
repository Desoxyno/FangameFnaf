#pragma once

#include <vector>

#include "../../dependencies/raylib/include/raylib.h"
#include "../../dependencies/raylib/include/raymath.h"
#include "../scenes/scenemanager.h"
#include "camera.hpp"
#include "gameobject.hpp"

class DebugMode
{
public:
    Ray ray = {0};
    RayCollision collision = {0};
    PlayerCamera* camera;
    std::vector<GameObject>* scene_objects;
    GameObject* selected_object;

    void ActivateDebugMode(PlayerCamera& pcamera, std::vector<GameObject>* objects);
    void Update();
    void Draw();
};
