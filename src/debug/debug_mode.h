#pragma once

#include <algorithm>
#include <cfloat>
#include <string>
#include <vector>

#include "engine/gameobject.hpp"
#include "engine/player_camera.hpp"
#include "engine/scenemanager.h"
#include "raylib.h"
#include "raymath.h"
#include "scenes/mainmenu.h"
#include "scenes/night1.h"
#include "utils/dropdown.h"

class DebugMode
{
public:
    enum class Mode
    {
        Position,
        Rotation,
        Scale
    };
    enum class SubMode
    {
        X,
        Y,
        Z
    };

    Dropdown level_menu{{10, 10, 180, 30}, {"Main Menu", "Night1"}};
    float amount_to_move = 1.0f;
    float scrollSpeed = 0.05f;

    std::unique_ptr<Scene> requestedScene = nullptr;

    Mode mode = Mode::Position;
    SubMode submode = SubMode::X;
    Ray ray = {0};
    RayCollision collision = {0};
    Scene* current_scene = nullptr;
    GameObject* selected_object;

    void ActivateDebugMode(Scene* scene);
    void Update();
    void Draw();
    void Reset();

    std::string ModeToString(Mode mode)
    {
        switch (mode)
        {
            case Mode::Position:
                return "Position";

            case Mode::Rotation:
                return "Rotation";
            case Mode::Scale:
                return "Scale";

            default:
                return "Unknown";
        }
    }

    std::string SubModeToString(SubMode submode)
    {
        switch (submode)
        {
            case SubMode::X:
                return "X";

            case SubMode::Y:
                return "Y";

            case SubMode::Z:
                return "Z";

            default:
                return "Unknown";
        }
    }
};
