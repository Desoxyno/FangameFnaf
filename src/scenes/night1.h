#pragma once

#include "engine/gameobject.hpp"
#include "engine/player_camera.hpp"
#include "engine/scene.hpp"
#include "game/systems/camera/camera_system.h"
#include "game/systems/tablet/tablet.h"

class Night1 : public Scene
{
private:
    bool InCams = false;

    Light lights[1];

    GameObject office;

    GameObject main_stage;

    Rectangle cam_btn{};

    Tablet tablet;

    PlayerCamera camera;

    Camera_System cam_system;

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