#include "config.h"
#include "intro.h"
#include "mainmenu.hpp"
#include "scenemanager.hpp"
#include "shader.hpp"

#define RLIGHTS_IMPLEMENTATION
#include "../dependencies/raylib/include/rlights.h"

#include <memory>

int main()
{
    // SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(1700, 800, "Fangame FNaF");

    if (!IsWindowReady()) {
        return -1;
    }

    SetTargetFPS(60);

    SceneManager scenemanager;

    Shader shader = getShader();

    scenemanager.shader = shader;

    // Create lights
    Light lights[1] = { 0 };
    lights[0] = CreateLight(LIGHT_POINT, (Vector3){4.0f, 3.5f, 0.0f}, Vector3Zero(), WHITE, shader);
    lights[0].color = Color{255, 255, 255, 255};

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

    while (!WindowShouldClose()){
        
        UpdateLightValues(shader, lights[0]);
        scenemanager.Update();
        scenemanager.Draw();
        
    


}

CloseWindow();

// SaveFileText()

return 0;

}