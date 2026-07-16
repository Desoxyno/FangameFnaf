#include "core/config.h"
#include "core/debug_mode.h"
#include "core/gamestate.h"
#include "core/global_variable.h"
#include "core/shader.h"
#include "scenes/intro.h"
#include "scenes/mainmenu.h"
#include "scenes/scenemanager.h"

#define RLIGHTS_IMPLEMENTATION
#include "../dependencies/raylib/include/rlights.h"

#include <memory>

int main()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT); // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(1700, 800, "Fangame FNaF");
    InitAudioDevice();

    if (!IsWindowReady())
    {
        return -1;
    }

    loadSave();

    SetTargetFPS(60);

    DebugMode debugmode;

    SceneManager scenemanager;

    Shader shader = getShader();

    scenemanager.shader = shader;

    if (!intro)
    {
        scenemanager.ChangeScene(std::make_unique<Intro>());
    }
    else
    {
        scenemanager.ChangeScene(std::make_unique<MainMenu>());
    }

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F1))
        {
            if (InDebug)
            {
                InDebug = false;
            }
            else
            {
                InDebug = true;
            }
        }

        if (InDebug)
        {
            debugmode.Update();
            debugmode.Draw();
        }
        else
        {
            scenemanager.Update();
            scenemanager.Draw();
        }
    }

    UnloadShader(shader);

    CloseWindow();

    // SaveFileText()

    return 0;
}