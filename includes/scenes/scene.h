#pragma once

#include <memory>
#include <raylib.h>
#include <span>
#include <string>
#include <vector>

#include "global_variables.h"
#include "models/gameobject.h"
#include "config/config.h"

class Scene {
    protected:
        std::vector<std::unique_ptr<GameObject>> scene_objects;

        Shader shader = LoadShader("assets/shaders/lighting.vs", "assets/shaders/lighting.fs");

        const int lightPositionLoc = GetShaderLocation(shader, "lightPosition");
        const int lightColorLoc = GetShaderLocation(shader, "lightColor");
        const int lightIntensityLoc = GetShaderLocation(shader, "lightIntensity");
        const int viewPositionLoc = GetShaderLocation(shader, "viewPosition");

        static constexpr Vector3 lightPosition = { 0.0f, 5.0f, 0.0f };
        static constexpr Vector3 lightColor = { 0.5f, 0.45f, 0.3f };
        static constexpr float lightIntensity = 2.0f;


    public:
        Scenes SceneWanted = NO_CHANGE;
        Camera camera = camera_mainmenu;

        Scene(const std::span<std::string> models_path) {
            assert(IsShaderValid(shader));
            shader.locs[SHADER_LOC_MATRIX_MVP] = GetShaderLocation(shader, "mvp");
            scene_objects.reserve(models_path.size());
            for (auto path : models_path) {
                scene_objects.emplace_back(std::make_unique<GameObject>(path.c_str(), shader));
            }
        }

        ~Scene() {
            UnloadShader(shader);
        }

        virtual void Update() {}
        virtual void Draw() {}

        const std::vector<std::unique_ptr<GameObject>>* GetSceneObjects() {
            return &scene_objects;
        }
};