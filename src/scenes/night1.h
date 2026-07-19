#pragma once

#include "engine/camera.hpp"
#include "engine/gameobject.hpp"
#include "engine/scene.hpp"
#include "game/systems/tablet/tablet.h"

class Night1 : public Scene
{
private:
    Light lights[1];

    GameObject office;

    Rectangle cam_btn{};

    Tablet tablet;

    PlayerCamera camera;

    bool has_entered = false;

    int current_hour = 12;
    int monitor_frame = 0;

    double starttime = 0.0;

public:
    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;
    PlayerCamera& GetCamera() override;
};