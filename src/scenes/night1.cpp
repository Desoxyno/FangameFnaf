#include "night1.h"

#include "config/config.h"
#include "engine/scene.hpp"
#include "mainmenu.h"
#include "utils/corefunc.h"
#include "utils/global_variable.h"

void Night1::Enter()
{
    starttime = GetTime();
    current_hour = 12;

    ResetLights();

    lights[0] = CreateLight(LIGHT_POINT, (Vector3) {-1.7f, 6.0f, -0.5f}, Vector3Zero(), WHITE, *shader);

    camera.changePosition({-1.7f, 4.0f, 1.6f});
    camera.changeTarget({-1.3f, 3.5f, -6.3f});

    tablet.positionM = {-1.7f, 4.0f, 1.6f};
    tablet.ApplyShader(shader);

    cam_btn = {0.0f, (float) GetScreenHeight() - 80.0f, (float) GetScreenWidth(), 80.0f};

    has_entered = true;

    if (!IsModelValid(office.model))
    {
        office.model = LoadModel("../assets/models/Office/office.glb");
        for (int i = 0; i < office.model.materialCount; i++)
        {
            office.model.materials[i].shader = *shader;
        }
    }

    office.name = "Office";
    tablet.positionM = {-1.7f, 4.0f, 1.6f};
    tablet.rotationM = {-180.0f, 0.0f, 0.0f};
    scene_objects.push_back(&office);
    scene_objects.push_back(&tablet);
}

PlayerCamera& Night1::GetCamera()
{
    return camera;
}

void Night1::Update()
{
    UpdateCamera(&camera.camera, camera_mode);
    for (GameObject* object : scene_objects)
    {
        object->Update();
    }

    if (IsButtonClicked(cam_btn))
    {
        TraceLog(LOG_INFO, "Tablet clicked");
        tablet.Switch();
    }

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
}

void Night1::Draw()
{
    BeginMode3D(camera.camera);

    DrawGrid(20, 10.0f);

    for (GameObject* object : scene_objects)
    {
        object->Draw();
    }

    EndMode3D();

    DrawFPS(GetScreenWidth() - 5, GetScreenHeight() - 5);

    if (IsButtonHovered(cam_btn))
    {
        DrawRectangleRec(cam_btn, {123, 0, 0, 50});
    }
    else
    {
        DrawRectangleRec(cam_btn, {255, 0, 0, 50});
    }

    if (InDebug)
    {
        DrawText("Debug Mode", GetScreenWidth() - 100, GetScreenHeight() - 20, 10, BLACK);
    }

    std::string text = std::to_string(current_hour) + " AM";

    int fontSize = 50;

    int textWidth = MeasureText(text.c_str(), fontSize);

    DrawText(text.c_str(), GetScreenWidth() - textWidth - 20, GetScreenHeight() - fontSize - 20, fontSize, RAYWHITE);
}

void Night1::Exit()
{
    for (GameObject* object : scene_objects)
    {
        object->Exit();
    }
}