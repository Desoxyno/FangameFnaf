#pragma once

#include <string>

#include "raylib.h"

class SecurityCamera
{
public:
    std::string name;
    Camera camera;
    SecurityCamera()
    {
        this->camera.position = (Vector3) {0.0f, 0.0f, 0.0f};
        this->camera.target = (Vector3) {0.0f, 0.0f, 0.0f};
        this->camera.up = (Vector3) {0.0f, 1.0f, 0.0f};
        this->camera.fovy = 45.0f;
        this->camera.projection = CAMERA_PERSPECTIVE;
    };
};