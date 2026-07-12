#include "intro.h"

#include "../core/config.h"
#include "../core/soundload.h"
#include "mainmenu.h"

void Intro::Enter()
{
    ResetLights();
    // Create lights
    lights[0] = CreateLight(LIGHT_POINT, (Vector3){12.0f, 3.5f, 0.0f}, Vector3Zero(), WHITE, *shader);
    lights[0].color = Color{255, 255, 255, 255};

    introStartTime = GetTime();

    sounds = multipleSoundLoad({"../assets/sounds/intro.mp3"});

    SetAudioStreamVolume(sounds[0].stream, 0.35);

    PlaySound(sounds[0]);

    camera.changePosition((Vector3){12.0f, 3.5f, 0.0f});
    camera.changeTarget((Vector3){0.0f, 2.0f, 0.0f});

    if (!IsModelValid(hallway.model))
    {
        hallway.model = LoadModel("../assets/models/Intro/Hallway.glb");
        for (int i = 0; i < hallway.model.materialCount; i++)
        {
            hallway.model.materials[i].shader = *shader;
        }
    }
}

void Intro::Draw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    BeginMode3D(camera.camera);

    if (IsModelValid(hallway.model))
    {
        DrawModel(hallway.model, hallway.position, 1.0f, WHITE);
    }

    EndMode3D();

    DrawText("Model by Oxyno83", GetScreenWidth() - 100, GetScreenHeight() - 20, 10, DARKGRAY);

    DrawFPS(5, 5);

    EndDrawing();
}

void Intro::Update()
{
    UpdateLightValues(*shader, lights[0]);

    double elapsed = GetTime() - introStartTime;

    if (elapsed >= 0.5)
    {
        nextScene = std::make_unique<MainMenu>();
    }
}

void Intro::Exit()
{
    UnloadModel(hallway.model);
}
