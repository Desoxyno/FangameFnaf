#pragma once

#include "scene.hpp"

class Intro : public Scene 
{
private:
GameObject hallway;
PlayerCamera camera;
double introStartTime;
public:
    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;
};