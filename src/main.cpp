#include "config.h"
#include "intro.h"
#include "mainmenu.h"
#include "scenemanager.hpp"
#include "shader.hpp"

#define RLIGHTS_IMPLEMENTATION
#include "../dependencies/raylib/include/rlights.h"

#include <memory>

int main()
{
    // SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(1700, 800, "Fangame FNaF");

    if (!IsWindowReady())
    {
        return -1;
    }

    SetTargetFPS(60);

    SceneManager scenemanager;

    Shader shader = getShader();

    scenemanager.shader = shader;

    LoadFileText("../saves/save.txt");

    int introPlayed = 0;

    if (!introPlayed)
    {
        scenemanager.ChangeScene(std::make_unique<Intro>());
    }
    else
    {
        scenemanager.ChangeScene(std::make_unique<MainMenu>());
    }

    while (!WindowShouldClose())
    {

        scenemanager.Update();
        scenemanager.Draw();
    }

    UnloadShader(shader);

    CloseWindow();

    // SaveFileText()

    return 0;
}