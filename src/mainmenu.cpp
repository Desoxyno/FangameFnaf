#include "mainmenu.h"

#include "config.h"
#include "corefunc.h"
#include "scene.hpp"

void MainMenu::Enter()
{
    ResetLights();
    lights[0].enabled = true;
    lights[0] = CreateLight(LIGHT_POINT, (Vector3){-2.5f, 6.5f, 0.0f}, Vector3Zero(), WHITE, *shader);
    lights[0].color = Color{255, 255, 255, 255};

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
    if (IsButtonClicked(play_btn))
    {
        // ChangeScene(std::make_unique<>);
        std::cout << "Clicked button";
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