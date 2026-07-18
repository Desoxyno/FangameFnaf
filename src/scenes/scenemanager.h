#pragma once

#include <memory>

#include "../../dependencies/raylib/include/raylib.h"
#include "../../dependencies/raylib/include/rlights.h"
#include "scene.hpp"

class SceneManager
{
public:
    std::unique_ptr<Scene> current_scene;

    Shader shader;
    Shader postShader;
    RenderTexture2D target;
    SceneManager();
    void ChangeScene(std::unique_ptr<Scene> newScene);
    void Update();
    void Draw();
};
