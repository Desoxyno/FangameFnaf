#pragma once

#include <raylib.h>
#include <raymath.h>
#include <span>
#include <string>
#include "global_variables.h"
#include "scenes/scene.h"
#include "utils/corefuncs.h"


class MainMenu : public Scene {
        const Font roboto = LoadFont("assets/fonts/Roboto/static/Roboto-Regular.ttf");
        const Rectangle play_btn = {15, 200, 150, 65};

    public:
        MainMenu(std::span<std::string> models_path) : Scene(models_path){
            assert(IsShaderValid(shader));
            shader.locs[SHADER_LOC_MATRIX_MVP] = GetShaderLocation(shader, "mvp");
            scene_objects.reserve(models_path.size());
            for (auto path : models_path) {
                scene_objects.emplace_back(std::make_unique<GameObject>(path.c_str(), shader));
            }
        }

        void Update() override {
            Ray ray = GetMouseRay(GetMousePosition(), camera);
            Vector3 point = Vector3Add(ray.position, Vector3Scale(ray.direction, 10.0f));
            camera.target = Vector3Lerp(camera.target, point, GetFrameTime());
            camera.target = Vector3Clamp(camera.target, {-1, -1, -1}, {1, 1, 1});
            UpdateCamera(&camera, CAMERA_CUSTOM);
            if (IsButtonClicked(play_btn)) {
                SceneWanted = NIGHT1;
            }
        }
        void Draw() override {

            SetShaderValue(shader, lightPositionLoc,
                        &lightPosition, SHADER_UNIFORM_VEC3);

            SetShaderValue(shader, lightColorLoc,
                        &lightColor, SHADER_UNIFORM_VEC3);

            SetShaderValue(shader, lightIntensityLoc,
                        &lightIntensity, SHADER_UNIFORM_FLOAT);

            SetShaderValue(shader, viewPositionLoc,
                        &camera.position, SHADER_UNIFORM_VEC3);


            BeginMode3D(camera);
            for (auto &object : scene_objects) {
                object->Draw();
            }
            EndMode3D();

            DrawRectangleRec(play_btn, {50, 0, 0, 0});

            DrawTextEx(roboto, "FNaF: The Last Seal", {5, 5}, 60, 2, WHITE);

            DrawTextEx(roboto, "Play", {15, 200}, 60, 2, WHITE);

            #ifdef DEBUG_BUILD
                DrawFPS(GetScreenWidth() - 90, 5);
            #endif

            
        }
};