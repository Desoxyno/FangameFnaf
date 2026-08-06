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

    float maxDist = 0.0f;

    Node* basement = nullptr;
    Node* office_left = nullptr;
    Node* office_front = nullptr;

    void Update() override;
    void Log();
    Springtrap();
    ~Springtrap();
};