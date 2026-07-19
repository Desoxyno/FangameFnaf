#include "intro.h"

#include "audio/soundload.h"
#include "config/config.h"
#include "mainmenu.h"
#include "utils/global_variable.h"

void Intro::Enter()
{
    ResetLights();
    // Create lights
    lights[0] = CreateLight(LIGHT_POINT, (Vector3) {12.0f, 3.5f, 0.0f}, Vector3Zero(), WHITE, *shader);
    lights[0].color = Color{255, 255, 255, 255};

    introStartTime = GetTime();

    sounds = multipleSoundLoad({"../assets/sounds/intro.mp3"});

    SetAudioStreamVolume(sounds[0].stream, 0.35);

    PlaySound(sounds[0]);

    camera.changePosition((Vector3) {12.0f, 3.5f, 0.0f});
    camera.changeTarget((Vector3) {0.0f, 2.0f, 0.0f});

    if (!IsModelValid(hallway.model))
    {
        hallway.model = LoadModel("../assets/models/Intro/Hallway.glb");
        for (int i = 0; i < hallway.model.materialCount; i++)
        {
            hallway.model.materials[i].shader = *shader;
        }
    }

    hallway.name = "Hallway";
    scene_objects.push_back(hallway);
}

PlayerCamera& Intro::GetCamera()
{
    return camera;
}

void Intro::Draw()
{
    BeginMode3D(camera.camera);

    for (GameObject& object : scene_objects)
    {
        Matrix transform = object.GetTransform();

        for (int i = 0; i < object.model.meshCount; i++)
        {
            DrawMesh(object.model.meshes[i], object.model.materials[object.model.meshMaterial[i]], transform);
        }
    }

    EndMode3D();

    DrawText("Model by Oxyno83", GetScreenWidth() - 100, GetScreenHeight() - 20, 10, DARKGRAY);
}

void Intro::Update()
{
    UpdateLightValues(*shader, lights[0]);

    UpdateCamera(&camera.camera, camera_mode);

    double elapsed = GetTime() - introStartTime;

    if (elapsed >= 1.5f && !changingScene)
    {
        changingScene = true;
        nextScene = std::make_unique<MainMenu>();
    }
}

void Intro::Exit()
{
    for (GameObject& object : scene_objects)
    {
        if (IsModelValid(object.model))
        {
            UnloadModel(object.model);
        }
    }
}
