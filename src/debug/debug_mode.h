#pragma once

#include <vector>

#include "engine/camera.hpp"
#include "engine/gameobject.hpp"
#include "engine/scenemanager.h"
#include "raylib.h"
#include "raymath.h"

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
