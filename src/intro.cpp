#include "intro.h"
#include "config.h"
#include "mainmenu.h"

void Intro::Enter()
{

    ResetLights();
    // Create lights
    lights[0] = CreateLight(LIGHT_POINT, (Vector3){12.0f, 3.5f, 0.0f}, Vector3Zero(), WHITE, *shader);
    lights[0].color = Color{255, 255, 255, 255};

    introStartTime = GetTime();

    camera.changePosition((Vector3){12.0f, 3.5f, 0.0f});
    camera.changeTarget((Vector3){0.0f, 2.0f, 0.0f});

    if (!IsModelValid(hallway.model))
    {
        hallway.model = LoadModel("../assets/3D_Models/Intro/Hallway.glb");
        for (int i = 0; i < hallway.model.materialCount; i++)
        {
            hallway.model.materials[i].shader = *shader;
        }
    }
}

void Intro::Draw()
{
    BeginMode3D(camera.camera);

    if (IsModelValid(hallway.model))
    {
        DrawModel(hallway.model, hallway.position, 1.0f, WHITE);
    }

    EndMode3D();

    DrawText("Model by Oxyno83", GetScreenWidth() - 100, GetScreenHeight() - 20, 10, DARKGRAY);

    DrawFPS(5, 5);
}

void Intro::Update()
{
    UpdateLightValues(*shader, lights[0]);

    double elapsed = GetTime() - introStartTime;

    if (elapsed >= 3)
    {
        nextScene = std::make_unique<MainMenu>();
    }
}

void Intro::Exit()
{
    UnloadModel(hallway.model);
}
