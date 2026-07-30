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
    GameObject office_hallway;

    std::vector<std::string> paths = {"../assets/models/Office/office.glb",
                                      "../assets/models/Map/Office_Hallway.glb",
                                      "../assets/models/Map/Parts&Service.glb",
                                      "../assets/models/Map/storage_room.glb"};
    std::vector<std::string> noms = {"Office", "Office Hallway", "Parts & Service", "Storage Room"};

    bool has_entered = false;
    PlayerCamera camera;

public:
    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;
    PlayerCamera& GetCamera() override;
};