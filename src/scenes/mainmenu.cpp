#include "mainmenu.h"

#include <memory>

#include "config/config.h"
#include "engine/scene.hpp"
#include "game/gamestate.h"
#include "night1.h"
#include "utils/corefunc.h"
#include "utils/global_variable.h"

void MainMenu::Enter()
{
    ResetLights();
    lights[0].enabled = true;
    lights[0] = CreateLight(LIGHT_POINT, (Vector3) {0.0f, 8.5f, -2.0f}, Vector3Zero(), WHITE, *shader);

    camera.changePosition((Vector3) {1.77f, 2.3f, 2.0f});
    camera.changeTarget((Vector3) {-1.0f, 0.85f, -4.2f});

    if (!IsModelValid(office.model))
    {
        office.model = LoadModel("../assets/models/Office/office.glb");
        for (int i = 0; i < office.model.materialCount; i++)
        {
            office.model.materials[i].shader = *shader;
        }
    }
    if (!IsModelValid(storage_room.model))
    {
        storage_room.model = LoadModel("../assets/models/Map/storage_room.glb");
        for (int i = 0; i < storage_room.model.materialCount; i++)
        {
            storage_room.model.materials[i].shader = *shader;
        }
    }

    has_entered = true;

    office.name = "Office";
    storage_room.name = "Storage Room";

    scene_objects.push_back(&office);
    scene_objects.push_back(&storage_room);
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
        object->Draw();
    }

    EndMode3D();

    DrawRectangleRec(play_btn, {0, 0, 0, 0});

    DrawText("A FNaF fangame", 5, 5, 80, DARKGRAY);

    DrawText("Play", 20, 200, 60, DARKGRAY);

    if (InDebug)
    {
        DrawText("Debug Mode", GetScreenWidth() - 100, GetScreenHeight() - 20, 10, BLACK);
    }

    DrawFPS(GetScreenWidth() - 5, GetScreenHeight() - 5);
}

void MainMenu::Exit()
{
    for (GameObject* object : scene_objects)
    {
        object->Exit();
    }
    scene_objects.clear();
}