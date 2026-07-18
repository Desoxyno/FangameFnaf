#pragma once

#include "engine/camera.hpp"
#include "engine/gameobject.hpp"
#include "engine/scene.hpp"

class Night1 : public Scene
{
private:
    enum class TabletState
    {
        Closed,
        Opening,
        Open,
        Closing
    };

    TabletState state = TabletState::Closed;

    Light lights[1];

    Rectangle cam_btn{};

    GameObject office;
    GameObject camera_monitor;

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