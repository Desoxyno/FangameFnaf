#include "debug_mode.h"

#include <cfloat>

void DebugMode::ActivateDebugMode(PlayerCamera& pcamera, std::vector<GameObject*>* objects)
{
    camera = &pcamera;
    scene_objects = objects;
    selected_object = nullptr;
}

void DebugMode::Update()
{
    if (!camera || !scene_objects)
    {
        return;
    }

    UpdateCamera(&camera->camera, CAMERA_FREE);

    // Changement de mode
    if (IsKeyPressed(KEY_W))
    {
        switch (mode)
        {
            case Mode::Position:
                mode = Mode::Rotation;
                break;

            case Mode::Rotation:
                mode = Mode::Position;
                break;
        }
    }

    // Changement d'axe
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

    // Déplacement de l'objet sélectionné
    if (selected_object)
    {
        if (IsKeyPressed(KEY_LEFT))
        {
            if (mode == Mode::Position)
            {
                switch (submode)
                {
                    case SubMode::X:
                        selected_object->positionM.x -= 1.0f;
                        break;
                    case SubMode::Y:
                        selected_object->positionM.y -= 1.0f;
                        break;
                    case SubMode::Z:
                        selected_object->positionM.z -= 1.0f;
                        break;
                }
            }
            else
            {
                switch (submode)
                {
                    case SubMode::X:
                        selected_object->rotationM.x -= 1.0f;
                        break;
                    case SubMode::Y:
                        selected_object->rotationM.y -= 1.0f;
                        break;
                    case SubMode::Z:
                        selected_object->rotationM.z -= 1.0f;
                        break;
                }
            }
        }

        if (IsKeyPressed(KEY_RIGHT))
        {
            if (mode == Mode::Position)
            {
                switch (submode)
                {
                    case SubMode::X:
                        selected_object->positionM.x += 1.0f;
                        break;
                    case SubMode::Y:
                        selected_object->positionM.y += 1.0f;
                        break;
                    case SubMode::Z:
                        selected_object->positionM.z += 1.0f;
                        break;
                }
            }
            else
            {
                switch (submode)
                {
                    case SubMode::X:
                        selected_object->rotationM.x += 1.0f;
                        break;
                    case SubMode::Y:
                        selected_object->rotationM.y += 1.0f;
                        break;
                    case SubMode::Z:
                        selected_object->rotationM.z += 1.0f;
                        break;
                }
            }
        }
    }

    // Sélection
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return;
    }

    ray = GetScreenToWorldRay(GetMousePosition(), camera->camera);

    selected_object = nullptr;

    float closestDistance = FLT_MAX;

    for (GameObject* object : *scene_objects)
    {
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

    if (!selected_object)
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

    BeginMode3D(camera->camera);

    selected_object->DrawBounds();

    EndMode3D();
}