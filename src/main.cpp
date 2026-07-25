#include "config/config.h"
#include "debug/debug_mode.h"
#include "engine/scenemanager.h"
#include "engine/shader.h"
#include "game/gamestate.h"
#include "scenes/mainmenu.h"
#include "utils/global_variable.h"

#define RLIGHTS_IMPLEMENTATION
#include <memory>

#include "rlights.h"

int main()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(1700, 800, "Fangame FNaF");
    InitAudioDevice();

    if (!IsWindowReady())
    {
        return -1;
    }

    TraceLog(LOG_INFO, "Raylib version: %s", RAYLIB_VERSION);

    loadSave();

    SetTargetFPS(60);

    SceneManager scenemanager;

    DebugMode debugmode;

    Shader shader = getShader();

    scenemanager.shader = shader;

    scenemanager.ChangeScene(std::make_unique<MainMenu>());

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F1))
        {
            InDebug = !InDebug;

            if (InDebug)
            {
                debugmode.ActivateDebugMode(scenemanager.current_scene.get());
            }
            else
            {
                debugmode.Reset();
            }
        }

        if (InDebug)
        {
            camera_mode = CAMERA_FREE;

            debugmode.Update();

            if (debugmode.requestedScene)
            {
                scenemanager.ChangeScene(std::move(debugmode.requestedScene));

                debugmode.ActivateDebugMode(scenemanager.current_scene.get());
            }
        }
        else
        {
            camera_mode = CAMERA_CUSTOM;

            scenemanager.Update();
        }

        BeginDrawing();

        ClearBackground(BLACK);

        scenemanager.Draw();

        if (InDebug)
        {
            debugmode.Draw();
        }

        EndDrawing();
    }

    UnloadShader(shader);

    CloseWindow();

    return 0;
}