#pragma once

#include <typeinfo>

#include "config/config.h"
#include "engine/gameobject.hpp"
#include "engine/player_camera.hpp"
#include "engine/scene.hpp"
#include "game/systems/animatronics/springtrap.h"
#include "game/systems/camera/camera_system.h"
#include "game/systems/tablet/tablet.h"
#include "mainmenu.h"
#include "rlights.h"
#include "utils/corefunc.h"
#include "utils/global_variable.h"

class Night1 : public Scene
{
private:
    bool InCams = false;

    Light lights[1];

    std::vector<std::string> paths = {"../assets/models/office/office.glb",
                                      "../assets/models/office/cardboard_boxes.gltf",
                                      "../assets/models/map/office_hallway.glb",
                                      "../assets/models/map/parts_services.glb",
                                      "../assets/models/map/storage_room.glb",
                                      "../assets/models/map/floor.glb"};
    std::vector<std::vector<std::string>> tex_paths = {{""},
                                                       {"../assets/textures/office/cardboard/cardboard_albedo.png",
                                                        "../assets/textures/office/cardboard/cardboard_normals.png",
                                                        "../assets/textures/office/cardboard/cardboard_roughness.png",
                                                        "../assets/textures/office/cardboard/cardboard_ao.png"},
                                                       {""},
                                                       {""},
                                                       {""},
                                                       {"../assets/textures/floor/tiles_albedo.png",
                                                        "../assets/textures/floor/tiles_normals.png",
                                                        "../assets/textures/floor/tiles_roughness.png",
                                                        "../assets/textures/floor/tiles_ao.png"}};
    std::vector<std::string> noms =
        {"Office", "Cardboard Boxes", "Office Hallway", "Parts & Service", "Storage Room", "Floor"};

    std::vector<GameObject::ObjectType> types = {GameObject::ObjectType::Structure,
                                                 GameObject::ObjectType::Object,
                                                 GameObject::ObjectType::Structure,
                                                 GameObject::ObjectType::Structure,
                                                 GameObject::ObjectType::Structure,
                                                 GameObject::ObjectType::Structure};

    Rectangle cam_btn{};

    Tablet tablet;

    PlayerCamera camera;

    Camera_System cam_system;

    Springtrap spring_trap;

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