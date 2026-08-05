#pragma once

#include <array>
#include <random>

#include "animatronic.h"
#include "node.h"
#include "raylib.h"

class Springtrap : public Animatronic
{

public:
    ModelAnimation jumpscare_anim;

    Node* current_node;
    Node* next_node;

    Vector3 current_pos;

    float maxDist = 0.0f;

    void Update() override;
    Springtrap();
};