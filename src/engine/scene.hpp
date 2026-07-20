#pragma once

#include <memory>
#include <vector>

#include "camera.hpp"
#include "gameobject.hpp"
#include "raylib.h"
#include "rlights.h"

class Scene
{
protected:
    Shader* shader = nullptr;

public:
    std::unique_ptr<Scene> nextScene = nullptr;
    std::vector<GameObject*> scene_objects;

    virtual void Enter() {}
    virtual void Update() {}
    virtual void Draw() {}
    virtual void Exit() {}
    virtual ~Scene() = default;

    virtual PlayerCamera& GetCamera() = 0;

    void SetShader(Shader* newShader)
    {
        shader = newShader;
    }
    void ChangeScene(std::unique_ptr<Scene> scene)
    {
        nextScene = std::move(scene);
    }
};