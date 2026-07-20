#include "scenemanager.h"

#include <memory>

#include "scene.hpp"

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
    if (!current_scene)
    {
        return;
    }

    if (current_state == Playing)
    {
        current_scene->Update();

        if (current_scene->nextScene)
        {
            pending_scene = std::move(current_scene->nextScene);
            current_state = FadeOut;
        }
    }

    if (current_state == FadeOut)
    {
        fade_alpha += 5;

        if (fade_alpha >= 255)
        {
            fade_alpha = 255;

            ChangeScene(std::move(pending_scene));

            current_state = FadeIn;
        }
    }

    if (current_state == FadeIn)
    {
        fade_alpha -= 5;

        if (fade_alpha <= 0)
        {
            fade_alpha = 0;
            current_state = Playing;
        }
    }
}

void SceneManager::Draw()
{
    // BeginTextureMode(target);

    if (current_scene)
    {
        current_scene->Draw();
    }

    // EndTextureMode();

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{0, 0, 0, fade_alpha});

    // ClearBackground(BLACK);

    // BeginShaderMode(postShader);

    // DrawTextureRec(target.texture, {0, 0, (float)target.texture.width, -(float)target.texture.height}, {0, 0},
    // WHITE);

    // EndShaderMode();
}
