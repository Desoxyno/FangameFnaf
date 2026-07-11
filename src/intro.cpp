#include "config.h"
#include "intro.h"
#include "mainmenu.hpp"

void Intro::Enter()
{   

    introStartTime = GetTime();

    camera.changePosition((Vector3){12.0f, 3.5f, 0.0f});
    camera.changeTarget((Vector3){0.0f, 2.0f, 0.0f});

    if (hallway.model.meshCount == 0) {
        hallway.model = LoadModel("../assets/3D_Models/Intro/Hallway.glb");
        for (int i = 0; i < hallway.model.materialCount; i++)
        {
            hallway.model.materials[i].shader = *shader;
        }
    }

}

void Intro::Draw() {
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera.camera);

            if (IsModelValid(hallway.model)) {
                DrawModel(hallway.model, hallway.position, 1.0f, WHITE);
            }

            EndMode3D();


            DrawText("Model by Oxyno83", GetScreenWidth() - 100, GetScreenHeight() - 20, 10, DARKGRAY);
            DrawFPS(5, 5);
            
    EndDrawing();
};

void Intro::Update() {

    double elapsed = GetTime() - introStartTime;

    if (elapsed >= 5) {
        nextScene = std::make_unique<MainMenu>();
    }
}
        
void Intro::Exit() {
        UnloadModel(hallway.model);
}



