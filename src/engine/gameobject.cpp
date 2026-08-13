#include "gameobject.hpp"

void GameObject::Draw(PlayerCamera& camera)
{
    Matrix transform = GetTransform();

    if (type != ObjectType::Structure)
    {
        for (int i = 0; i < model.meshCount; i++)
        {
            if (useOptimisations && !IsVisible(model.meshes[i], transform, camera))
            {
                continue;
            }

            R3D_DrawMeshPro(model.meshes[i], model.materials[model.meshMaterials[i]], transform);
        }
    }
    else
    {
        for (int i = 0; i < model.meshCount; i++)
        {
            R3D_DrawMeshPro(model.meshes[i], model.materials[model.meshMaterials[i]], transform);
        }
    }
}

void GameObject::DrawBounds()
{
    R3D_BoundingBox box = model.aabb;
    Matrix transform = GetTransform();

    BoundingBox transformed = {{FLT_MAX, FLT_MAX, FLT_MAX}, {-FLT_MAX, -FLT_MAX, -FLT_MAX}};

    for (int i = 0; i < 8; i++)
    {
        Vector3 p = Vector3Transform(
            {(i & 1) ? box.max.x : box.min.x, (i & 2) ? box.max.y : box.min.y, (i & 4) ? box.max.z : box.min.z},
            transform);

        transformed.min = Vector3Min(transformed.min, p);
        transformed.max = Vector3Max(transformed.max, p);
    }

    DrawBoundingBox(transformed, RED);
}

void GameObject::Update() {}

void GameObject::Exit()
{
    R3D_UnloadModel(model, true);
    model = {};
}