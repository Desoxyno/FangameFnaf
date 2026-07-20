#pragma once

#include <cfloat>
#include <string>
#include <vector>

#include "engine/camera.hpp"
#include "engine/gameobject.hpp"
#include "engine/scenemanager.h"
#include "raylib.h"
#include "raymath.h"

class DebugMode
{
public:
    enum class Mode
    {
        Position,
        Rotation
    };
    enum class SubMode
    {
        X,
        Y,
        Z
    };
    Mode mode = Mode::Position;
    SubMode submode = SubMode::X;
    Ray ray = {0};
    RayCollision collision = {0};
    PlayerCamera* camera;
    std::vector<GameObject*>* scene_objects;
    GameObject* selected_object;

    void ActivateDebugMode(PlayerCamera& pcamera, std::vector<GameObject*>* objects);
    void Update();
    void Draw();

    std::string ModeToString(Mode mode)
    {
        switch (mode)
        {
            case Mode::Position:
                return "Position";

            case Mode::Rotation:
                return "Rotation";

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
