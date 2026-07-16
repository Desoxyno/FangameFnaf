#include "mainmenu.h"

#include "../core/config.h"
#include "../core/corefunc.h"
#include "../core/gamestate.h"
#include "night1.h"
#include "scene.hpp"

#include <memory>

void MainMenu::Enter()
{
    ResetLights();
    lights[0].enabled = true;
    lights[0] = CreateLight(LIGHT_POINT, (Vector3){0.0f, 8.5f, -2.0f}, Vector3Zero(), WHITE, *shader);

    camera.changePosition((Vector3){2.2f, 5.0f, 5.5f});
    camera.changeTarget((Vector3){0.0f, 4.0f, -1.0f});

    if (!IsModelValid(office.model))
    {
        office.model = LoadModel("../assets/models/Office/office.glb");
        for (int i = 0; i < office.model.materialCount; i++)
        {
            office.model.materials[i].shader = *shader;
        }
    }

    has_entered = true;
}

void MainMenu::Update()
{
    UpdateCamera(&camera.camera, CAMERA_PERSPECTIVE);

    if (IsButtonClicked(play_btn))
    {
        ChangeScene(std::make_unique<Night1>());
    }
}

void MainMenu::Draw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    BeginMode3D(camera.camera);

    DrawGrid(20, 10.0f);

    if (IsModelValid(office.model))
    {
        DrawModel(office.model, office.position, 1.0f, WHITE);
        // Shader lightning = LoadShader("lighting.vs", "lightning.fs");
    }

    EndMode3D();

    DrawRectangleRec(play_btn, {0, 0, 0, 0});

    DrawText("A FNaF fangame", 5, 5, 80, DARKGRAY);

    DrawText("Play", 20, 200, 60, DARKGRAY);

    DrawFPS(GetScreenWidth() - 5, GetScreenHeight() - 5);

    EndDrawing();
}

void MainMenu::Exit()
{
    UnloadModel(office.model);
}