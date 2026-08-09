#pragma once

#include <memory>

#include "config/config.h"
#include "engine/gameobject.hpp"
#include "engine/player_camera.hpp"
#include "engine/scene.hpp"
#include "game/gamestate.h"
#include "night1.h"
#include "rlights.h"
#include "utils/corefunc.h"
#include "utils/global_variable.h"

class MainMenu : public Scene
{
private:
    const Rectangle play_btn = {15, 200, 150, 65};
    Light lights[1];

    Font roboto;

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

    bool has_entered = false;
    PlayerCamera camera;

public:
    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;
    PlayerCamera& GetCamera() override;
};