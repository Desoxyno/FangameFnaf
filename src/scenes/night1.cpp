#include "night1.h"

#include "../core/config.h"
#include "../core/corefunc.h"
#include "../core/global_variable.h"
#include "mainmenu.h"
#include "scene.hpp"

void Night1::Enter()
{
    starttime = GetTime();
    current_hour = 12;

    monitor_frame = 0;
    state = TabletState::Closed;

    cam_btn = {0.0f, GetScreenHeight() - 80.0f, (float) GetScreenWidth(), 80.0f};

    ResetLights();

    lights[0] = CreateLight(LIGHT_POINT, (Vector3) {-1.7f, 6.0f, -0.5f}, Vector3Zero(), WHITE, *shader);

    camera.changePosition({-1.7f, 4.0f, 1.6f});
    camera.changeTarget({-1.3f, 3.5f, -6.3f});

    camera_monitor.positionM = {-1.0f, 4.8f, -2.0f};

    if (!IsModelValid(office.model))
    {
        office.model = LoadModel("../assets/models/Office/office.glb");

        for (int i = 0; i < office.model.materialCount; i++)
        {
            office.model.materials[i].shader = *shader;
        }
    }

    if (!IsModelValid(camera_monitor.model))
    {
        camera_monitor.model = LoadModel("../assets/models/Office/camera_monitor.glb");

        for (int i = 0; i < camera_monitor.model.materialCount; i++)
        {
            camera_monitor.model.materials[i].shader = *shader;
        }
    }

    camera_monitor.animations =
        LoadModelAnimations("../assets/models/Office/camera_monitor.glb", &camera_monitor.animationCount);

    TraceLog(LOG_INFO, "Animations: %d", camera_monitor.animationCount);

    has_entered = true;

    scene_objects.push_back(office);
    scene_objects.push_back(camera_monitor);
}

PlayerCamera& Night1::GetCamera()
{
    return camera;
}

void Night1::Update()
{
    UpdateCamera(&camera.camera, camera_mode);

    // Gestion de l'heure
    if (GetTime() - starttime >= NIGHT_DURATION / HOURS_PER_NIGHT)
    {
        if (current_hour == 12)
        {
            current_hour = 1;
        }
        else
        {
            current_hour++;
        }

        starttime = GetTime();
    }

    if (current_hour == HOURS_PER_NIGHT)
    {
        ChangeScene(std::make_unique<MainMenu>());
        return;
    }

    // Ouverture tablette
    if (IsButtonHovered(cam_btn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && state == TabletState::Closed)
    {
        monitor_frame = 0;
        state = TabletState::Opening;
    }

    switch (state)
    {
        case TabletState::Closed:
            break;

        case TabletState::Opening:
        {
            if (camera_monitor.animationCount > 0)
            {
                UpdateModelAnimation(camera_monitor.model, camera_monitor.animations[0], monitor_frame);

                monitor_frame++;

                if (monitor_frame >= camera_monitor.animations[0].keyframeCount)
                {
                    monitor_frame = camera_monitor.animations[0].keyframeCount - 1;

                    state = TabletState::Open;
                }
            }

            break;
        }

        case TabletState::Open:
            break;

        case TabletState::Closing:
            break;
    }
}

void Night1::Draw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    BeginMode3D(camera.camera);

    DrawGrid(20, 10.0f);

    for (GameObject& object : scene_objects)
    {
        Matrix transform = object.GetTransform();

        for (int i = 0; i < object.model.meshCount; i++)
        {
            DrawMesh(object.model.meshes[i], object.model.materials[object.model.meshMaterial[i]], transform);
        }
    }

    if (state != TabletState::Closed)
    {
        // DrawModel(camera_monitor.model, camera_monitor.position, 1.0f, WHITE);
    }

    EndMode3D();

    if (IsButtonHovered(cam_btn))
    {
        DrawRectangleRec(cam_btn, {255, 0, 0, 20});
    }
    else
    {
        DrawRectangleRec(cam_btn, {100, 100, 100, 20});
    }

    DrawFPS(GetScreenWidth() - 5, GetScreenHeight() - 5);

    if (InDebug)
    {
        DrawText("Debug Mode", GetScreenWidth() - 100, GetScreenHeight() - 20, 10, BLACK);
    }

    std::string text = std::to_string(current_hour) + " AM";

    int fontSize = 50;

    int textWidth = MeasureText(text.c_str(), fontSize);

    DrawText(text.c_str(), GetScreenWidth() - textWidth - 20, GetScreenHeight() - fontSize - 20, fontSize, RAYWHITE);

    EndDrawing();
}

void Night1::Exit()
{
    UnloadModel(office.model);

    if (camera_monitor.animations != nullptr)
    {
        UnloadModelAnimations(camera_monitor.animations, camera_monitor.animationCount);
    }

    UnloadModel(camera_monitor.model);
}