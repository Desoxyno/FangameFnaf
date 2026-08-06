#pragma once

#include <array>
#include <random>

#include "engine/gameobject.hpp"
#include "node.h"
#include "raylib.h"

class Springtrap : public GameObject
{

public:
    ModelAnimation jumpscare_anim;

    Node* previous_node = nullptr;
    Node* current_node = nullptr;
    Node* next_node = nullptr;

    float speed = 0.5f;

    Node* basement = nullptr;
    Node* office_left = nullptr;
    Node* office_front = nullptr;

    void Update() override;
    void Log();
    void LogPos() {
        std::cout << name << " X: " << positionM.x << " Y: " << positionM.y << " Z: " << positionM.z << std::endl;
    }
    Springtrap();
    ~Springtrap();
};