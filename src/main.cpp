#include "config/config.h"
#include "debug/debug_mode.h"
#include "engine/scenemanager.h"
#include "engine/shader.h"
#include "game/gamestate.h"
#include "scenes/intro.h"
#include "scenes/mainmenu.h"
#include "utils/global_variable.h"

#define RLIGHTS_IMPLEMENTATION
#include <memory>

#include "../dependencies/raylib/include/rlights.h"

int main()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(1700, 800, "Fangame FNaF");
    InitAudioDevice();

    if (!IsWindowReady())
    {
        return -1;
    }

    TraceLog(LOG_INFO, "Raylib version: %s", RAYLIB_VERSION);

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
        // INPUT + UPDATE
        if (IsKeyPressed(KEY_F1))
        {
            InDebug = !InDebug;

            if (InDebug)
            {
                debugmode.ActivateDebugMode(scenemanager.current_scene->GetCamera(),
                                            &scenemanager.current_scene->scene_objects);
            }
        }

        if (InDebug)
        {
            camera_mode = CAMERA_FREE;
            debugmode.Update();
        }
        else
        {
            camera_mode = CAMERA_CUSTOM;
            scenemanager.Update();
        }

        // DRAW
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

    // SaveFileText()

    return 0;
}