#pragma once

#include "scene.hpp"
#include "../dependencies/raylib/include/raylib.h"
#include "../dependencies/raylib/include/rlights.h"
#include <memory>

class SceneManager {
    private:
        std::unique_ptr<Scene> current_scene;

    public:
        Shader shader;
        void ChangeScene(std::unique_ptr<Scene> newScene);
        void Update();
        void Draw();


};

