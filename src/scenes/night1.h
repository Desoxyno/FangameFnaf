#pragma once

#include "engine/gameobject.hpp"
#include "engine/player_camera.hpp"
#include "engine/scene.hpp"
#include "game/systems/animatronics/springtrap.h"
#include "game/systems/camera/camera_system.h"
#include "game/systems/tablet/tablet.h"

class Night1 : public Scene
{
private:
    bool InCams = false;

    Light lights[1];

    // Rooms
    GameObject office;
    GameObject main_stage;
    GameObject storage_room;
    GameObject partsservice;

    std::vector<std::string> paths = {"../assets/models/Office/office.glb",
                                      "../assets/models/Map/Office_Hallway.glb",
                                      "../assets/models/Map/Parts&Service.glb",
                                      "../assets/models/Map/storage_room.glb"};
    std::vector<std::string> noms = {"Office", "Office Hallway", "Parts & Service", "Storage Room"};

    Rectangle cam_btn{};

    Tablet tablet;

    PlayerCamera camera;

    Camera_System cam_system;

    Springtrap spring_trap;

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