#include "mainmenu.h"

void MainMenu::Enter()
{
    roboto = LoadFont("../assets/fonts/Roboto/static/Roboto-Regular.ttf");

    ResetLights();
    lights[0].enabled = true;
    lights[0] = CreateLight(LIGHT_POINT, (Vector3) {0.0f, 8.5f, -2.0f}, Vector3Zero(), WHITE, *shader);

    camera.changePosition((Vector3) {1.77f, 2.3f, 2.0f});
    camera.changeTarget((Vector3) {-1.0f, 0.85f, -4.2f});

    preparingModels(paths, tex_paths, noms, scene_objects, types);
}

PlayerCamera& MainMenu::GetCamera()
{
    return camera;
}

void MainMenu::Update()
{
    UpdateCamera(&camera.camera, camera_mode);

    for (GameObject* object : scene_objects)
    {
        object->Update();
    }

    if (IsButtonClicked(play_btn))
    {
        ChangeScene(std::make_unique<Night1>());
    }
}

void MainMenu::Draw()
{
    BeginMode3D(camera.camera);

    DrawGrid(20, 10.0f);

    for (GameObject* object : scene_objects)
    {
        if (!IsVisible(object, camera) && useOptimisations)
        {
            continue;
        }
        object->Draw();
    }

    EndMode3D();

    DrawRectangleRec(play_btn, {50, 0, 0, 0});

    DrawTextEx(roboto, "FNaF: The Last Seal", {5, 5}, 60, 2, WHITE);

    DrawTextEx(roboto, "Play", {15, 200}, 60, 2, WHITE);

    if (InDebug)
    {
        DrawText("Debug Mode", GetScreenWidth() - 100, GetScreenHeight() - 20, 10, BLACK);
    }

    DrawFPS(GetScreenWidth() - 90, 5);
}

void MainMenu::Exit()
{
    for (GameObject* object : scene_objects)
    {
        object->Exit();
    }
    scene_objects.clear();
}