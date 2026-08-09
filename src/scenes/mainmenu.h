#pragma once

#include "engine/gameobject.hpp"
#include "engine/player_camera.hpp"
#include "engine/scene.hpp"

class MainMenu : public Scene
{
private:
    Rectangle play_btn = {15, 200, 150, 65};
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

    bool has_entered = false;
    PlayerCamera camera;

public:
    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;
    PlayerCamera& GetCamera() override;
};