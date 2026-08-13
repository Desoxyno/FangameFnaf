#include "mainmenu.h"

void MainMenu::Enter()
{
    roboto = LoadFont("../assets/fonts/Roboto/static/Roboto-Regular.ttf");

    light = R3D_CreateOmniLight((Vector3) {1.0f, 2.5f, -1.0f}, 10.0f, WHITE, 0.1f);

    shadowMap = R3D_LoadShadowMap(R3D_LIGHT_OMNI);

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
    R3D_Begin(camera.camera);

    R3D_PushLightEx(light, shadowMap, true);

    DrawGrid(20, 10.0f);

    for (GameObject* object : scene_objects)
    {
        object->Draw(camera);
    }

    R3D_End();

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