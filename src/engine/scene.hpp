#pragma once

#include <memory>
#include <vector>

#include "gameobject.hpp"
#include "player_camera.hpp"
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
    virtual ~Scene()
    {
        scene_objects.clear();
    }

    virtual PlayerCamera& GetCamera() = 0;

    void SetShader(Shader* newShader)
    {
        shader = newShader;
    }
    void ChangeScene(std::unique_ptr<Scene> scene)
    {
        nextScene = std::move(scene);
    }
    void preparingModels(std::vector<std::string> paths,
                         std::vector<std::string> names,
                         std::vector<GameObject*>& scene_objects)
    {
        for (size_t i = 0; i < paths.size(); i++)
        {
            GameObject* newObject = new GameObject();

            newObject->model = LoadModel(paths[i].c_str());
            newObject->name = names[i];

            for (int j = 0; j < newObject->model.materialCount; j++)
            {
                newObject->model.materials[j].shader = *shader;
            }

            scene_objects.push_back(newObject);
        }
    }
};