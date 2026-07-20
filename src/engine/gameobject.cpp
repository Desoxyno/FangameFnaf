#include "gameobject.hpp"

#include <cfloat>
#include <cmath>

void GameObject::Draw()
{
    Matrix transform = GetTransform();

    for (int i = 0; i < model.meshCount; i++)
    {
        DrawMesh(model.meshes[i], model.materials[model.meshMaterial[i]], transform);
    }
}

void GameObject::DrawBounds()
{
    BoundingBox box = GetModelBoundingBox(model);

    Vector3 corners[8] = {{box.min.x, box.min.y, box.min.z},
                          {box.max.x, box.min.y, box.min.z},
                          {box.min.x, box.max.y, box.min.z},
                          {box.max.x, box.max.y, box.min.z},
                          {box.min.x, box.min.y, box.max.z},
                          {box.max.x, box.min.y, box.max.z},
                          {box.min.x, box.max.y, box.max.z},
                          {box.max.x, box.max.y, box.max.z}};

    Matrix transform = GetTransform();

    BoundingBox transformed = {Vector3{FLT_MAX, FLT_MAX, FLT_MAX}, Vector3{-FLT_MAX, -FLT_MAX, -FLT_MAX}};

    for (int i = 0; i < 8; i++)
    {
        Vector3 p = Vector3Transform(corners[i], transform);

        transformed.min.x = fmin(transformed.min.x, p.x);
        transformed.min.y = fmin(transformed.min.y, p.y);
        transformed.min.z = fmin(transformed.min.z, p.z);

        transformed.max.x = fmax(transformed.max.x, p.x);
        transformed.max.y = fmax(transformed.max.y, p.y);
        transformed.max.z = fmax(transformed.max.z, p.z);
    }

    DrawBoundingBox(transformed, RED);
}

void GameObject::Update() {}

void GameObject::Exit()
{
    UnloadModel(model);
}