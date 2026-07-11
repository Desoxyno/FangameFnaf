#pragma once

#include "../dependencies/raylib/include/raylib.h"
#include "../dependencies/raylib/include/rlights.h"
#include "scene.hpp"
#include <memory>

class SceneManager
{
  private:
    std::unique_ptr<Scene> current_scene;

  public:
    Shader shader;
    Shader postShader;
    RenderTexture2D target;
    SceneManager();
    void ChangeScene(std::unique_ptr<Scene> newScene);
    void Update();
    void Draw();
};
