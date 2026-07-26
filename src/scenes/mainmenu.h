#pragma once

#include "engine/gameobject.hpp"
#include "engine/player_camera.hpp"
#include "engine/scene.hpp"

class MainMenu : public Scene
{
private:
    Rectangle play_btn = {15, 200, 150, 65};
    Light lights[1];

    GameObject office;
    GameObject storage_room;

    bool has_entered = false;
    PlayerCamera camera;

public:
    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;
    PlayerCamera& GetCamera() override;
};