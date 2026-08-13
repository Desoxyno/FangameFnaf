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
                         std::vector<std::vector<std::string>> tex_paths,
                         std::vector<std::string> names,
                         std::vector<GameObject*>& scene_objects,
                         std::vector<GameObject::ObjectType> types)
    {
        for (size_t i = 0; i < paths.size(); i++)
        {
            if (tex_paths[i].size() < 3)
            {
                TraceLog(LOG_ERROR,
                         "tex_paths[%zu] a seulement %zu éléments pour l'objet '%s' (3 attendus)",
                         i,
                         tex_paths[i].size(),
                         names[i].c_str());
                continue;
            }
            GameObject* newObject = new GameObject();

            newObject->model = R3D_LoadModel(paths[i].c_str());
            newObject->name = names[i];
            newObject->type = types[i];

            Texture2D albedo = LoadTexture(tex_paths[i][0].c_str());
            Texture2D normal = LoadTexture(tex_paths[i][1].c_str());
            Texture2D orm = LoadTexture(tex_paths[i][2].c_str());

            for (int m = 0; m < newObject->model.materialCount; m++)
            {
                newObject->model.materials[m].albedo.texture = albedo;
                newObject->model.materials[m].normal.texture = normal;
                newObject->model.materials[m].orm.texture = orm;
            }

            scene_objects.push_back(newObject);
        }
    }
};