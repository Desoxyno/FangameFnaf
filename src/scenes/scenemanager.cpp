#include "scenemanager.h"

#include "scene.hpp"

#include <memory>

SceneManager::SceneManager()
{
    // target = LoadRenderTexture(1700, 800);
    // postShader = LoadShader(0, "../assets/shaders/posterization.fs");
}
void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene)
{
    if (current_scene)
    {
        current_scene->Exit();
    }

    newScene->SetShader(&shader);

    current_scene = std::move(newScene);
    current_scene->Enter();
}

void SceneManager::Update()
{
    if (current_scene)
    {
        current_scene->Update();

        if (current_scene->nextScene)
        {
            ChangeScene(std::move(current_scene->nextScene));
        }
    }
}

void SceneManager::Draw()
{
    // BeginTextureMode(target);

    ClearBackground(BLACK);

    if (current_scene)
        current_scene->Draw();

    // EndTextureMode();

    // BeginDrawing();

    // ClearBackground(BLACK);

    // BeginShaderMode(postShader);

    // DrawTextureRec(target.texture, {0, 0, (float)target.texture.width, -(float)target.texture.height}, {0, 0},
    // WHITE);

    // EndShaderMode();

    // EndDrawing();
}
