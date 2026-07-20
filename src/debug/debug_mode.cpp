#include "debug_mode.h"

#include <cfloat>

void DebugMode::ActivateDebugMode(Scene* scene)
{
    current_scene = scene;
    selected_object = nullptr;
}

void DebugMode::Update()
{
    if (!current_scene)
    {
        return;
    }

    PlayerCamera& camera = current_scene->GetCamera();
    auto& scene_objects = current_scene->scene_objects;

    // Caméra libre uniquement avec clic droit
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        UpdateCamera(&camera.camera, CAMERA_FREE);
    }

    // Changement de scène depuis le menu debug
    if (level_menu.Update())
    {
        switch (level_menu.selected)
        {
            case 0:
                requestedScene = std::make_unique<Intro>();
                break;

            case 1:
                requestedScene = std::make_unique<MainMenu>();
                break;

            case 2:
                requestedScene = std::make_unique<Night1>();
                break;
        }

        selected_object = nullptr;
        return;
    }

    // Changement Position / Rotation
    if (IsKeyPressed(KEY_W))
    {
        mode = (mode == Mode::Position) ? Mode::Rotation : Mode::Position;
    }

    // Changement axe
    if (IsKeyPressed(KEY_X))
    {
        switch (submode)
        {
            case SubMode::X:
                submode = SubMode::Y;
                break;

            case SubMode::Y:
                submode = SubMode::Z;
                break;

            case SubMode::Z:
                submode = SubMode::X;
                break;
        }
    }

    // Modification objet sélectionné
    if (selected_object)
    {
        float direction = 0;

        if (IsKeyPressed(KEY_LEFT))
        {
            direction = -1;
        }

        if (IsKeyPressed(KEY_RIGHT))
        {
            direction = 1;
        }

        if (direction != 0)
        {
            if (mode == Mode::Position)
            {
                switch (submode)
                {
                    case SubMode::X:
                        selected_object->positionM.x += direction;
                        break;

                    case SubMode::Y:
                        selected_object->positionM.y += direction;
                        break;

                    case SubMode::Z:
                        selected_object->positionM.z += direction;
                        break;
                }
            }
            else
            {
                switch (submode)
                {
                    case SubMode::X:
                        selected_object->rotationM.x += direction;
                        break;

                    case SubMode::Y:
                        selected_object->rotationM.y += direction;
                        break;

                    case SubMode::Z:
                        selected_object->rotationM.z += direction;
                        break;
                }
            }
        }
    }

    // Sélection objet
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return;
    }

    ray = GetScreenToWorldRay(GetMousePosition(), camera.camera);

    selected_object = nullptr;

    float closestDistance = FLT_MAX;

    for (GameObject* object : scene_objects)
    {
        if (!object)
        {
            continue;
        }

        Matrix transform = object->GetTransform();

        for (int i = 0; i < object->model.meshCount; i++)
        {
            RayCollision hit = GetRayCollisionMesh(ray, object->model.meshes[i], transform);

            if (hit.hit && hit.distance < closestDistance)
            {
                closestDistance = hit.distance;
                collision = hit;
                selected_object = object;
            }
        }
    }

    if (selected_object)
    {
        TraceLog(LOG_INFO, "Selected: %s", selected_object->name.c_str());
    }
}

void DebugMode::Draw()
{
    DrawText("Debug Mode", 10, 10, 20, RAYWHITE);

    DrawFPS(5, 35);

    DrawText(ModeToString(mode).c_str(), 10, 140, 20, RAYWHITE);

    DrawText(SubModeToString(submode).c_str(), 10, 160, 20, RAYWHITE);

    level_menu.Draw();

    if (!selected_object || !current_scene)
    {
        return;
    }

    std::string name = "Object: " + selected_object->name;

    std::string position = "Position X:" + std::to_string(selected_object->positionM.x) +
                           " Y:" + std::to_string(selected_object->positionM.y) +
                           " Z:" + std::to_string(selected_object->positionM.z);

    std::string rotation = "Rotation X:" + std::to_string(selected_object->rotationM.x) +
                           " Y:" + std::to_string(selected_object->rotationM.y) +
                           " Z:" + std::to_string(selected_object->rotationM.z);

    DrawText(name.c_str(), 10, 70, 20, RAYWHITE);

    DrawText(position.c_str(), 10, 100, 20, RAYWHITE);

    DrawText(rotation.c_str(), 10, 120, 20, RAYWHITE);

    BeginMode3D(current_scene->GetCamera().camera);

    selected_object->DrawBounds();

    EndMode3D();
}

void DebugMode::Reset()
{
    current_scene = nullptr;
    selected_object = nullptr;
}