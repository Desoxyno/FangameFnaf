#pragma once

#include <vector>

#include "engine/camera.hpp"
#include "engine/gameobject.hpp"
#include "engine/scene.hpp"

class Intro : public Scene
{
private:
    std::vector<Sound> sounds;
    Light lights[1];
    GameObject hallway;
    PlayerCamera camera;
    double introStartTime;
    bool changingScene = false;

public:
    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;
    PlayerCamera& GetCamera() override;
};