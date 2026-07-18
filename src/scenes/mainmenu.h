#pragma once

#include "../core/camera.hpp"
#include "../core/gameobject.hpp"
#include "scene.hpp"

class MainMenu : public Scene
{
private:
    Rectangle play_btn = {15, 200, 150, 65};
    Light lights[1];
    GameObject office;
    bool has_entered = false;
    PlayerCamera camera;

public:
    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;
    PlayerCamera& GetCamera() override;
};