#pragma once

#include "../../dependencies/raylib/include/raylib.h"
#include "../../dependencies/raylib/include/rlights.h"
#include "../core/gameobject.hpp"

#include <memory>
#include <vector>

class Scene
{
  protected:
    Shader* shader = nullptr;

  public:
    std::unique_ptr<Scene> nextScene = nullptr;
    std::vector<GameObject> scene_objects;

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