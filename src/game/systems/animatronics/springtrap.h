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

    float speed = 1.0f;

    Node* Basement_Entrance = nullptr;

    Node* Office_Left = nullptr;
    Node* Office_Front = nullptr;

    Node* Hallway_Employees = nullptr;
    Node* Hallway_Service = nullptr;

    void Update() override;
    void Log();
    void LogPos() {
        std::cout << name << " X: " << positionM.x << " Y: " << positionM.y << " Z: " << positionM.z << std::endl;
    }
    Springtrap();
    ~Springtrap();
};