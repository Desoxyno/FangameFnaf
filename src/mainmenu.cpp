#include "config.h"

#include "scene.hpp"
#include "mainmenu.hpp"

void MainMenu::Enter() {

    camera.changePosition((Vector3){2.2f, 5.0f, 5.5f});
    camera.changeTarget((Vector3){0.0f, 4.0f, -1.0f});

    if (!IsModelValid(office.model)) {
        office.model = LoadModel("../assets/3D_Models/Office/office.glb");
        for (int i = 0; i < office.model.materialCount; i++)
        {
            office.model.materials[i].shader = *shader;
        }
    }

    has_entered = true;
}
        
void MainMenu::Update() {

}

void MainMenu::Draw() {
    BeginDrawing();

        ClearBackground(BLACK);
                    
        BeginMode3D(camera.camera);

            DrawGrid(20, 10.0f);

                 if (IsModelValid(office.model)) {
                    DrawModel(office.model, office.position, 1.0f, WHITE);
                    // Shader lightning = LoadShader("lighting.vs", "lightning.fs");
                }

            EndMode3D();

            DrawText("A FNaF fangame", 5, 5, 50, DARKGRAY);

                    
            DrawFPS(GetScreenWidth() - 5, GetScreenHeight() - 5);
                    
    EndDrawing();
}

void MainMenu::Exit() {
    
}