#pragma once

#include <array>

#include "animatronic.h"
#include "raylib.h"

class Springtrap : public Animatronic
{
public:
    ModelAnimation jumpscare_anim;
    int current_point = 0;
    std::array<Vector3, 2> path_points = {{{15.0f, 11.0f, 0.0f}, {-15.0f, -11.0f, 0.0f}}};

    Vector3 current_pos = {0, 0, 0};
    Vector3 next_pos = {0, 0, 0};

    float maxDist = 0.0f;

    void Update() override;
};