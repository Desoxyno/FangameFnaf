#pragma once

#include "config/config.h"
#include "global_variables.h"
#include "models/gameobject.h"
#include <raymath.h>
#include "node.h"
#include "raylib.h"

#ifdef DEBUG_BUILD
    #include <iostream>
#endif

class Springtrap : public GameObject
{
    public:
        ModelAnimation jumpscare_anim;

        Node* previous_node = nullptr;
        Node* current_node = &nodes[0];
        Node* next_node = &nodes[0];

        const float speed = 0.75f;

        void Update() {
            #ifdef DEBUG_BUILD
            // Log Function
            static float timer = 0;

            timer += GetFrameTime();

            if (timer >= 1.0f) {
                this->Log();
                timer = 0.0f;

            }
            #endif

            if (position == Vector3{next_node->position.x, 0, next_node->position.z})
                {
                    previous_node = current_node;
                    current_node = next_node;
                    next_node = previous_node->search_next_node();
                    position = current_node->position;
                    
                }
                position = Vector3MoveTowards(position, {next_node->position.x, 0, next_node->position.z} , speed * GetFrameTime());

        };

        #ifdef DEBUG_BUILD
            void Log() {
                current_node->LogPos();
                LogPos();
                next_node->LogPos();
            };

            void LogPos() {
                std::cout << "Springtrap position : " << " X: " << position.x << " Y: " << position.y << " Z: " << position.z << std::endl;
            }
        #endif

        Springtrap() : GameObject("assets/models/cube_no_tex.glb", shader){
            position = {-24, 0, 0.3};
        };
};