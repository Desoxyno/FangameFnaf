#pragma once

#include <vector>

#include "../core/camera.hpp"
#include "../core/gameobject.hpp"
#include "scene.hpp"

class Intro : public Scene
{
private:
    std::vector<Sound> sounds;
    Light lights[1];
    GameObject hallway;
    PlayerCamera camera;
    double introStartTime;

public:
    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;
    PlayerCamera& GetCamera() override;
};