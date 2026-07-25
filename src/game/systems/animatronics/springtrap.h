#pragma once

#include <array>

#include "animatronic.h"
#include "raylib.h"

class Springtrap : public Animatronic
{
public:
    ModelAnimation jumpscare_anim;
    std::array<Vector3, 1> path_points = {{15.0f, 512.0f, 520.0f}};

    Vector3 current_pos = {0, 0, 0};
    Vector3 next_pos = {0, 0, 0};

    float maxDist = 0.0f;

    void UpdatePosition() override;
};