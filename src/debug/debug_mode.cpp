#include "debug_mode.h"

#include <cfloat>

void DebugMode::ActivateDebugMode(PlayerCamera& pcamera, std::vector<GameObject>* objects)
{
    camera = &pcamera;
    scene_objects = objects;

    selected_object = nullptr;
}

void DebugMode::Update()
{
    if (!camera || !scene_objects)
    {
        return;
    }

    UpdateCamera(&camera->camera, CAMERA_FREE);

    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return;
    }

    ray = GetScreenToWorldRay(GetMousePosition(), camera->camera);

    selected_object = nullptr;

    float closestDistance = FLT_MAX;

    for (GameObject& object : *scene_objects)
    {
        Matrix transform = object.GetTransform();

        for (int i = 0; i < object.model.meshCount; i++)
        {
            RayCollision hit = GetRayCollisionMesh(ray, object.model.meshes[i], transform);

            if (hit.hit && hit.distance < closestDistance)
            {
                closestDistance = hit.distance;

                collision = hit;
                selected_object = &object;
            }
        }
    }

    if (selected_object)
    {
        TraceLog(LOG_DEBUG, "%s touched", selected_object->name.c_str());
    }
}

void DebugMode::Draw()
{
    if (!selected_object || !camera)
    {
        return;
    }

    BeginMode3D(camera->camera);

    BoundingBox box = GetModelBoundingBox(selected_object->model);

    DrawBoundingBox(box, RED);

    EndMode3D();
}