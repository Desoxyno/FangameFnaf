#pragma once

#include <cassert>
#include <raylib.h>

class GameObject {
    protected:
        Model model;
        Vector3 position = {0, 0, 0};
        float scale = 1;

    public:
        GameObject(const char* model_path, const Shader& shader) {
            model = LoadModel(model_path);
            for (int i = 0; i < model.materialCount; ++i)
                model.materials[i].shader = shader;
            assert(IsModelValid(model));
        }

        ~GameObject() {
            UnloadModel(model);
        }

        const Model* GetModel() {
            return &model;
        }
        Vector3* GetPosition() {
            return &position;
        }
        float* GetScale() {
            return &scale;
        }

        virtual void Draw() {
            DrawModel(model, position, scale, WHITE);
        }
        virtual void Update() {}
};