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
                         std::vector<GameObject*>& scene_objects)
    {
        for (size_t i = 0; i < paths.size(); i++)
        {
            if (tex_paths[i].size() < 4)
            {
                TraceLog(LOG_ERROR,
                         "tex_paths[%zu] a seulement %zu éléments pour l'objet '%s' (4 attendus)",
                         i,
                         tex_paths[i].size(),
                         names[i].c_str());
                continue;
            }
            GameObject* newObject = new GameObject();

            newObject->model = LoadModel(paths[i].c_str());
            newObject->name = names[i];

            if (tex_paths[i][0] != "")
            {
                Texture2D albedo = LoadTexture(tex_paths[i][0].c_str());
                for (int m = 0; m < newObject->model.materialCount; m++)
                {
                    newObject->model.materials[m].maps[MATERIAL_MAP_ALBEDO].texture = albedo;
                }
            }
            if (tex_paths[i][1] != "")
            {
                Texture2D normal = LoadTexture(tex_paths[i][1].c_str());
                for (int m = 0; m < newObject->model.materialCount; m++)
                {
                    newObject->model.materials[m].maps[MATERIAL_MAP_NORMAL].texture = normal;
                }
            }
            if (tex_paths[i][2] != "")
            {
                Texture2D roughness = LoadTexture(tex_paths[i][2].c_str());
                for (int m = 0; m < newObject->model.materialCount; m++)
                {
                    newObject->model.materials[m].maps[MATERIAL_MAP_ROUGHNESS].texture = roughness;
                }
            }
            if (tex_paths[i][3] != "")
            {
                Texture2D ao = LoadTexture(tex_paths[i][3].c_str());
                for (int m = 0; m < newObject->model.materialCount; m++)
                {
                    newObject->model.materials[m].maps[MATERIAL_MAP_OCCLUSION].texture = ao;
                }
            }

            newObject->model.materials[0].maps[MATERIAL_MAP_METALNESS].value = 0.0f;

            for (int j = 0; j < newObject->model.materialCount; j++)
            {
                newObject->model.materials[j].shader = *shader;
            }

            scene_objects.push_back(newObject);
        }
    }
};