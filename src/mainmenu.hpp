#pragma once

#include "scene.hpp"

class MainMenu : public Scene 
{
private:
GameObject office;
bool has_entered = false;
PlayerCamera camera;
public:
    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;
};