#pragma once

#include <raylib.h>
#include <raymath.h>
#include <span>
#include <string>
#include "ennemies/springtrap/springtrap.h"
#include "scenes/scene.h"
#include "utils/timer.h"
#include "global_variables.h"
#include "sound/sound.h"

class Night1 : public Scene {
        const Font roboto = LoadFont("../assets/fonts/Roboto/static/Roboto-Regular.ttf");

        Timer timer;

        SoundLoader soundloader;

    public:
        Night1(std::span<std::string> models_path) : Scene(models_path){
            assert(IsShaderValid(shader));
            shader.locs[SHADER_LOC_MATRIX_MVP] = GetShaderLocation(shader, "mvp");
            scene_objects.reserve(models_path.size());
            for (auto path : models_path) {
                scene_objects.emplace_back(std::make_unique<GameObject>(path.c_str(), shader));
            }
            scene_objects.emplace_back(std::make_unique<Springtrap>());
            soundloader.Load("assets/sounds/night.mp3", 0.8);
        }

        void Update() override {
            if (timer.hasTimerEndedYet(std::chrono::duration<double>(NIGHT_DURATION))) {
                SceneWanted = MAIN_MENU;
                return;
            }
            for (auto &object : scene_objects) {
                object->Update();
            }
            camera.target = Vector3Lerp(camera.target, GetMouseRay(GetMousePosition(), camera).position, 0.3);
            UpdateCamera(&camera, CAMERA_CUSTOM);
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

            #ifdef DEBUG_BUILD
                DrawFPS(GetScreenWidth() - 90, 5);
            #endif

            
        }
};