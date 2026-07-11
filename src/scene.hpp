#pragma once

#include "../dependencies/raylib/include/raylib.h"
#include "../dependencies/raylib/include/rlights.h"

#include <memory>

class Scene
{
  protected:
    Shader* shader = nullptr;

  public:
    std::unique_ptr<Scene> nextScene = nullptr;

    virtual void Enter() {}
    virtual void Update() {}
    virtual void Draw() {}
    virtual void Exit() {}
    virtual ~Scene() = default;

    void SetShader(Shader* newShader)
    {
        shader = newShader;
    }
    void ChangeScene(std::unique_ptr<Scene> scene)
    {
        nextScene = std::move(scene);
    }
};