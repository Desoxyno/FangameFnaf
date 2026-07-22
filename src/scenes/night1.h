#pragma once

#include "engine/gameobject.hpp"
#include "engine/player_camera.hpp"
#include "engine/scene.hpp"
#include "game/systems/animatronics/animatronic.h"
#include "game/systems/tablet/tablet.h"

class Night1 : public Scene
{
private:
    Light lights[1];

    GameObject office;

    GameObject main_stage;

    Rectangle cam_btn{};

    Tablet tablet;

    PlayerCamera camera;

    Animatronic spring_trap;

    std::vector<Animatronic*> animatronics;

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